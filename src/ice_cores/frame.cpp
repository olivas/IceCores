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
  std::lock_guard<std::mutex> lock(mutex_);
  map_[key] = frame_object;
  cv_.notify_all();
}

const FrameObjectConstPtr&
Frame::wait_for(const std::string& key) const {
  std::unique_lock<std::mutex> lock(mutex_);
  cv_.wait(lock, [this, &key]{ return bool(map_.find(key) != map_.end()); });
  return map_.at(key);
}

size_t
Frame::size() const {
  return map_.size();
}

