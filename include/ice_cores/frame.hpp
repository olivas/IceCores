#pragma once
#include <mutex>
#include <map>

#include <ice_cores/frame_object.hpp>

class Frame{
public:
  const FrameObjectConstPtr& get(const std::string& key) const;
  void put(const std::string& key, const FrameObjectPtr& frame_object);
  size_t size() const;
  
private:
  std::map<std::string, FrameObjectConstPtr> map_;
  std::mutex mutex_;
};

