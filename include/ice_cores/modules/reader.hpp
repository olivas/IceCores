#pragma once

#include <ice_cores/frame_object.hpp>
#include <ice_cores/frame.hpp>
#include <ice_cores/module.hpp>

class Reader: public Module{
  void operator()(Frame& frame);
  std::string name();
};

