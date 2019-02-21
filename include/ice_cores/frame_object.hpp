#pragma once
#include <memory>

class FrameObject{
public:
  virtual ~FrameObject(){};
private:
};

using FrameObjectPtr = std::shared_ptr<FrameObject>;
using FrameObjectConstPtr = std::shared_ptr<const FrameObject>;
