#pragma once
#include <vector>
#include <thread>
  
class JoinThreads{
  std::vector<std::thread>& threads;
public:
  explicit JoinThreads(std::vector<std::thread>& threads):
    threads(threads){}
  ~join_threads(){
    for(auto& t : threads){
      if(t.joinable())
    	t.join();
    }
  }
};

class ThreadPool{
  std::atomic_bool done;
  thread_safe_queue<std::function<void()>> work_queue;
  std::vector<std::thread> threads;
  JoinThreads joiner;
  
public:
  ThreadPool(): done(false), joiner(threads){
    unsigned const thread_count = std::thread::hardware_concurrency();
    try{
      for(unsigned i{0}; i<thread_count; ++i){
	auto worker_thread = [this](){
			       while(!done){
				 if(!work_queue.empty()){
				   auto task = work_queue.pop();
				   (*task)();
				 }else{
				   std::this_thread::yield();
				 }
			       }
			     };
	threads.push_back(std::thread(worker_thread));
      }
    }catch(...){
      done=true;
      throw;
    }
  }
  
  ~ThreadPool(){ done=true; }
  template<typename FunctionType>
  void submit(FunctionType f){
    work_queue.push(std::function<void()>(f));
  }
};

