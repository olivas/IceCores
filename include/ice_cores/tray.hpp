#pragma once

#include <memory>
#include <vector>
#include <thread>
#include <ostream>
#include <chrono>

#include <ice_cores/frame_object.hpp>
#include <ice_cores/frame.hpp>
#include <ice_cores/module.hpp>
#include <ice_cores/lock_free_queue.hpp>

namespace IceCores{

  // We need at least dummy sources and sinks
  // Now FrameSources aren't copy-able if we have
  // atomic members.
  class EmptyFrameSource{
  public:

    EmptyFrameSource(unsigned n_frames = std::numeric_limits<unsigned>::max()):
      frame_counter_(0),
      n_frames_(n_frames)
    {
      std::cout<<"n_frames = "<<n_frames<<std::endl;
    }

    EmptyFrameSource(EmptyFrameSource&& source){
      frame_counter_.store(source.frame_counter_.load());
      n_frames_ = source.n_frames_;
    }

    auto begin(){
      frame_counter_=0; // reset
      return std::make_unique<Frame>();
    }
    auto end(){ return nullptr; }

    std::unique_ptr<Frame> next(){
      ++frame_counter_;
      std::cout<<"frame "<<frame_counter_.load()
	       <<" of "<<n_frames_<<std::endl;
      if(frame_counter_.load() >= n_frames_)
          return nullptr;
      return std::make_unique<Frame>();
    }

    auto count(){ return frame_counter_.load(); }
    std::ostream& operator<<(std::ostream& os){
      os<<"Frame["<<frame_counter_.load()<<"]\n";
      return os;
    }

  private:
    std::atomic<unsigned> frame_counter_;
    unsigned n_frames_;
  };

  struct DummyFrameSink{
    // This class does nothing
    void push(std::shared_ptr<Frame>& frame){};
  };

  template<typename FrameSource, typename FrameSink>
  class Tray{
  public:
    Tray(FrameSource&& frame_source,
	 const FrameSink& frame_sink):
      frame_source_(std::move(frame_source)),
      frame_sink_(frame_sink){}

    void add(std::unique_ptr<Module>& module){
      modules_.push_back(std::move(module));
    }

    void execute(){
      // Get the first frame from the source
      auto frame_ptr = frame_source_.begin();
      // Loop over all the frames until you reach the end
      while(frame_ptr != frame_source_.end()){
	// Execute each module in order for each frame
	for(auto&& m : modules_){
	  (*m)(*frame_ptr);
	}
	// Push the frame into the sink
	frame_sink_.push(*frame_ptr);
	// Get the next frame
	frame_ptr = frame_source_.next();
      }
    }

    void execute_pipelines(unsigned n_pipelines = 1){
      // If N == 0 then go with the hardware concurrency
      // We want 1 thread for the main thread
      // 1 thread to read
      // 1 thread to write
      // and 1 thread per pipeline
      unsigned hwc{std::thread::hardware_concurrency()};
      unsigned n_threads{n_pipelines + 3};
      if(n_pipelines + 3 > hwc){
	std::cout<<"WARN: Oversubscription launching "
		 <<n_threads<<" threads."<<std::endl;
	std::cout<<"WARN: Hardware concurrency = "<<hwc<<std::endl;
      }

      using FrameQueue = IceCores::lock_free_queue<Frame>;
      std::shared_ptr<FrameQueue> input_q;
      input_q = std::make_shared<FrameQueue>();
      std::shared_ptr<FrameQueue> output_q;
      output_q = std::make_shared<FrameQueue>();

      // first start loading the queue
      // capture the queue by reference
      auto frame_ptr = frame_source_.begin();
      // launch a thread the loads the queue from the FrameSource
      std::thread load_queue([this, &input_q, &frame_ptr](){
			       while(frame_ptr != frame_source_.end()){
				 input_q->push(*frame_ptr);
				 frame_ptr = frame_source_.next();
				 std::this_thread::sleep_for(std::chrono::seconds(1));
			       }
			     }
	);

      // Create a pipeline which calls the modules
      // for each frame in order.
      auto pipeline = [this, &input_q, &output_q](){
			while(!input_q->empty()){
			  auto f = input_q->pop();
			  for(auto&& m : modules_){
			    (*m)(*f);// f is a shared_ptr<Frame>
			  }
			  output_q->push(*f);
			  std::this_thread::sleep_for(std::chrono::seconds(1));
			}
		      };

      std::vector<std::thread> pipeline_threads;
      for(unsigned i{0}; i < n_pipelines; ++i){
	pipeline_threads.emplace_back(std::thread(pipeline));
      }

      std::thread unload_queue([this, &output_q, &input_q](){
				 while(!output_q->empty()){
				   auto f = output_q->pop();
				   if(f){
				     frame_sink_.push(f);
				   }
				   std::this_thread::sleep_for(std::chrono::seconds(1));
				 }
			       }
	);


      load_queue.join();
      for(auto&& t: pipeline_threads)
	t.join();
      unload_queue.join();

    }

  private:
    std::vector<std::unique_ptr<Module>> modules_;
    FrameSource frame_source_;
    FrameSink frame_sink_;
  };
}
