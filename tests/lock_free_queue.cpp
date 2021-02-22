#define BOOST_TEST_MODULE My_Test
#include <boost/test/included/unit_test.hpp>

#include <ice_cores/lock_free_queue.hpp>

using IceCores::lock_free_queue;

BOOST_AUTO_TEST_CASE(instantiation){
  lock_free_queue<int> q;  
}

BOOST_AUTO_TEST_CASE(methods){
  lock_free_queue<int> q;
  q.push(0);
  q.push(1);
  q.push(2);
  q.push(3);

  // This is a FIFO structure
  // First-In, First-Out
  auto result = q.pop();
  BOOST_TEST(*result == 0);
}
