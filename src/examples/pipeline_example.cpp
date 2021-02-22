#include <memory>
#include <iostream>

#include <ice_cores/frame_object.hpp>
#include <ice_cores/frame.hpp>
#include <ice_cores/module.hpp>
#include <ice_cores/modules/reader.hpp>
#include <ice_cores/modules/writer.hpp>
#include <ice_cores/tray.hpp>

class RecoResult : public FrameObject {};

class LineFit : public Module{
public:
  
  virtual void operator()(Frame& frame) override {
    std::cout<<"LineFit(start)"<<std::endl; 
    //std::this_thread::sleep_for(std::chrono::seconds(5));
    std::shared_ptr<RecoResult> r(new RecoResult);
    frame.put("LineFitResult", r);
    std::cout<<"LineFit(stop)"<<std::endl;
  }
  
  virtual std::string name() override {
    return std::string("LineFit");
  }
};

class TensorOfInertia : public Module{
public:
  
  virtual void operator()(Frame& frame) override {
    std::cout<<"TensorOfInertia(start)"<<std::endl;
    //std::this_thread::sleep_for(std::chrono::seconds(5));
    std::shared_ptr<RecoResult> r(new RecoResult);
    frame.put("ToIResult", r);
    std::cout<<"TensorOfInertia(stop)"<<std::endl;
  }
  
  virtual std::string name() override {
    return std::string("TensorOfInertia");
  }
};

int main(){

  std::unique_ptr<Module> linefit = std::make_unique<LineFit>();
  std::unique_ptr<Module> toi = std::make_unique<TensorOfInertia>();

  unsigned n_frames{10};
  IceCores::EmptyFrameSource source(n_frames);
  IceCores::DummyFrameSink sink;
  
  IceCores::Tray tray(std::move(source), sink);
  tray.add(linefit);
  tray.add(toi);
  tray.execute_pipelines(2);  
}
