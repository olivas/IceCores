// Simple illustration of a race condition
// To build, remember to link to pthread, e.g.: 
// $ clang++ -std=c++17 -lpthread simple_race_illustration.cpp
// $ a.out 10000
// The standard specification above isn't
// strictly necessary for recent versions of clang.
#include <iostream>
#include <thread>
#include <string>
#include <map>
#include <vector>
#include <mutex>

using std::cout;
using std::endl;
using std::map;
using std::vector;
using std::string;
using std::mutex;
using std::lock_guard;

  class Frame{
    map<string, vector<unsigned>> data_;
    mutex mutex_;
  
  public:
    void write(const string& key, const vector<unsigned>& value){
      lock_guard<mutex> lock(mutex_);
      data_[key] = value;
    }
    void read(const string& key, vector<unsigned>& value){
      //lock_guard<mutex> lock(mutex_);
      value = data_[key];
    }
  };
  
  int main(int argc, char** argv){
  
    Frame frame;
  
    auto write = [&frame](unsigned N){
  		 for(unsigned i{0}; i < 100; ++i){
  		   vector<unsigned> v;
  		   if(i%2){
  		     for(unsigned j{0}; j < N; ++j){
  		       v.push_back(j);
  		     }
  		   }else{
  		     for(unsigned j{N}; j > 0; --j){
  		       v.push_back(j);
  		     }
  		   }			   
  		   frame.write("value", v);
  		 }
  	       };
  
    auto read = [&frame](unsigned N){
  		for(unsigned i{0}; i<N; ++i){
  		  vector<unsigned> v;
  		  frame.read("value", v);
  		  for(auto value: v)
  		    cout<<value<<" ";
  		  cout<<endl;
  		}
  	      };
  
    std::thread t1(write, 80);  
    std::thread t2(read, 100);
    t1.join();
    t2.join();
  }


