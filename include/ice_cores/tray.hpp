#include <memory>
#include <vector>

#include <ice_cores/frame_object.hpp>
#include <ice_cores/frame.hpp>
#include <ice_cores/module.hpp>

namespace IceCores{

  // We need at least dummy sources and sinks
  class EmptyFrameSource : public std::iterator<std::input_iterator_tag, Frame>{
    // This creates and serves up empty frames    
  };

  class DummyFrameSink : public std::iterator<std::output_iterator_tag, Frame>{
    // This class does nothing
  };
  
  
  template<typename FrameSource, typename FrameSink>
  class Tray{
  public:
    Tray(const FrameSource& frame_source,
	 const FrameSink& frame_sink):
      frame_source_(frame_source),
      frame_sink_(frame_sink){}

    void add(const Module& module){
      modules_.push_back(std::make_unique<Module>(module));
    }

    void execute(){
      // Get the first frame from the source
      typename FrameSource::iterator frame_iter = begin(frame_source_);
      // Loop over all the frames until you reach the end
      while(frame_iter != end(frame_source_)){
	// Execute each module in order for each frame
	for(auto&& m : modules_){
	  (*m)(*frame_iter);
	}
	// Push the frame into the sink
	*frame_iter >> frame_sink_;
	// Get the next frame
	++frame_iter;
      }
    }

  private:
    std::vector<std::unique_ptr<Module>> modules_;
    FrameSource frame_source_;
    FrameSink frame_sink_;
  };
}
