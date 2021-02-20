#pragma once

#include <ice_cores/frame.hpp>

class Module{
public:
  virtual void operator()(Frame& frame) = 0;
  virtual std::string name() = 0;
  virtual ~Module(){};
private:
};

