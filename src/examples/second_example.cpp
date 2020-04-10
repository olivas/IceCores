#include <any>
#include <map>
#include <mutex>
#include <condition_variable>
#include <memory>
#include <vector>
#include <thread>
#include <iostream>

#include <ice_cores/frame_object.hpp>
#include <ice_cores/frame.hpp>
#include <ice_cores/module.hpp>
#include <ice_cores/modules/reader.hpp>
#include <ice_cores/modules/writer.hpp>
#include <ice_cores/tray.hpp>

class RecoResult : public FrameObject {};

class LineFit : public Module{
  void operator()(Frame& frame){
    std::cout<<"LineFit(start)"<<std::endl;
    //std::this_thread::sleep_for(std::chrono::seconds(5));
    std::shared_ptr<RecoResult> r(new RecoResult);
    frame.put("LineFitResult", r);
    std::cout<<"LineFit(stop)"<<std::endl;
  }

  std::string name(){ return std::string("LineFit"); }
};

class TensorOfInertia : public Module{
  void operator()(Frame& frame){
    std::cout<<"TensorOfInertia(start)"<<std::endl;
    //std::this_thread::sleep_for(std::chrono::seconds(5));
    std::shared_ptr<RecoResult> r(new RecoResult);
    frame.put("ToIResult", r);
    std::cout<<"TensorOfInertia(stop)"<<std::endl;
  }

  std::string name(){ return std::string("TensorOfInertia"); }
};

int main(){

  std::unique_ptr<Module> reader(new Reader);
  std::unique_ptr<Module> linefit(new LineFit);
  std::unique_ptr<Module> toi(new TensorOfInertia);
  std::unique_ptr<Module> writer(new Writer);

  Tray tray;
  tray.add(reader);
  tray.add(linefit);
  tray.add(toi);
  tray.add(writer);
  tray.execute(1);
  
}
