#include <map>
#include <vector>
#include <thread>
#include <iostream>

#include <ice_cores/frame_object.hpp>
#include <ice_cores/frame.hpp>
#include <ice_cores/module.hpp>
#include <ice_cores/tray.hpp>

void Tray::add(std::unique_ptr<Module>& module){
  modules_.push_back(std::move(module));
}

void Tray::execute(unsigned n_frames){
  std::cout<<"Tray::execute Processing "<<n_frames<<" frames."<<std::endl;
  unsigned processed_frames{0};

  std::cout<<"Number of Modules = "<<modules_.size()<<std::endl;
  for(auto&& m : modules_){
    std::cout<<m->name()<<std::endl;
  }
  
  for(unsigned processed_frames{0};
      processed_frames < n_frames;
      processed_frames++){
    Frame frame;
    std::vector<std::thread> threads;
    for(auto&& m : modules_){
      std::cout<<"Launching thread for '"<<m->name()<<"'"<<std::endl;
      std::thread t([&frame, module = std::move(m)]{ (*module)(frame); });
      // m goes out of scope
      // it's a dangling reference.
      // we really, really need a self-contained closure
      threads.push_back(std::move(t));
    }
    for(auto&& t : threads){
      t.join();
    }
  }
}

