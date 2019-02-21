#include <memory>
#include <vector>

#include <ice_cores/frame_object.hpp>
#include <ice_cores/frame.hpp>
#include <ice_cores/module.hpp>

class Tray{
public:
  void add(std::unique_ptr<Module>& module);
  void execute(unsigned n_frames);
  
private:
  std::vector<std::unique_ptr<Module>> modules_;
};

