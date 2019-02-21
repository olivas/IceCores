#include <thread>
#include <iostream>

class Execute{
public:
  void operator()(){
    n_calls_++;
    std::cout<<"n calls"<<n_calls_<<std::endl;
  }
private:
  unsigned n_calls_ = 0;
};

int main(){

  Execute exe;  
  std::thread t1(exe);
  std::thread t2(exe);
  //std::thread t2(t1);  // <- This is not legal.

  t1.join();
  t2.join();
}
