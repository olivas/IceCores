#pragma once

#include <atomic>
#include <memory>

namespace IceCores{
  
  template <typename T>
  class lock_free_queue{
    // Lock-free queue data structure with races,
    // shamelessly copied from Anthony Williams'
    // "Concurrency in C++: Practical Multithreading"
  private:
    struct node{
      node(): next(nullptr){}      
      std::shared_ptr<T> data;
      node* next;     
    };

    std::atomic<node*> head;
    std::atomic<node*> tail;

    node* pop_head(){
      node* const old_head = head.load();
      if(old_head == tail.load()){
	return nullptr;
      }
      head.store(old_head->next);
      return old_head;
    }

  public:
    lock_free_queue();
    ~lock_free_queue();
    std::shared_ptr<T> pop();
    void push(T new_value);
    bool empty() const;

    
    lock_free_queue(): head(new node), tail(head.load()){}
    lock_free_queue(const lock_free_queue&) = delete;
    lock_free_queue& operator=(const lock_free_queue&) = delete;

    ~lock_free_queue(){
      while(node* const old_head = head.load()){
	head.store(old_head->next);
	delete old_head;
      }
    }

    std::shared_ptr<T> pop(){
      node* old_head = pop_head();
      if(!old_head){
	return std::shared_ptr<T>();
      }
      std::shared_ptr<T> const result(old_head->data);
      delete old_head;
      return result;
    }

    void push(T new_value){
      std::shared_ptr<T> new_data(std::make_shared<T>(new_value));
      node* p = new node;
      node* const old_tail = tail.load();
      old_tail->data.swap(new_data);
      old_tail->next = p;
      tail.store(p);
    }

    bool empty() const {
      node* const old_head = head.load();
      return (old_head == tail.load());
    }
    
  };
  

}
