#include <iostream>
#include <thread>
#include <ice_cores/modules/writer.hpp>

void Writer::operator()(Frame& frame){
  std::cout<<"Writer(start)"<<std::endl;
  //std::this_thread::sleep_for(std::chrono::seconds(6));  
  std::cout<<"There are "<<frame.size()<<" elements in this frame."<<std::endl;
  std::cout<<"Writer(stop)"<<std::endl;
}

std::string Writer::name(){ return std::string("Writer"); }
