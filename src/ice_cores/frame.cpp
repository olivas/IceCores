#include <map>
#include <vector>
#include <thread>
#include <iostream>

#include <ice_cores/frame_object.hpp>
#include <ice_cores/frame.hpp>

const FrameObjectConstPtr&
Frame::get(const std::string& key) const {
  return map_.at(key);
}

void
Frame::put(const std::string& key, const FrameObjectPtr& frame_object){
  map_[key] = frame_object;
}

size_t
Frame::size() const {
  return map_.size();
}

