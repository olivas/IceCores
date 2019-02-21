#include <iostream>
#include <thread>
#include <vector>
#include <ice_cores/frame_object.hpp>
#include <ice_cores/modules/reader.hpp>

template <typename T>
class Vector : public FrameObject {
public:
  void push_back(T value){ vector_.push_back(value); }
private:
    std::vector<T> vector_;
};

void Reader::operator()(Frame& frame){
  std::cout<<"Reader(start)"<<std::endl;
  std::shared_ptr<Vector<double>>  hits(new Vector<double>);
  hits->push_back(1.0);
  std::this_thread::sleep_for(std::chrono::seconds(1));  
  frame.put(std::string("hits"), hits);
  std::cout<<"Reader(stop)"<<std::endl;
}

std::string Reader::name(){ return std::string("Reader"); }

