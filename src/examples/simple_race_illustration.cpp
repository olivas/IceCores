// Simple illustration of a race condition
// To build, remember to link to pthread, e.g.: 
// $ clang++ -std=c++17 -lpthread simple_race_illustration.cpp
// $ a.out 10000
// The standard specification above isn't
// strictly necessary for recent versions of clang.
#include <iostream>
#include <thread>
#include <string>
  
static int counter = 0;
  
void increment_by(unsigned N){
  for(int i{0}; i<N; ++i)
    ++counter;
}
  
int main(int argc, char** argv){
  int N{std::stoi(argv[1])};
  std::thread t1(increment_by, N);
  std::thread t2(increment_by, N);
  t1.join();
  t2.join();
  std::cout<<"counter = "<<counter<<std::endl; 
}


