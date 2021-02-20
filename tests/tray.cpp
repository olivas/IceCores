#define BOOST_TEST_MODULE My_Test
#include <boost/test/included/unit_test.hpp>

#include <ice_cores/tray.hpp>

using IceCores::EmptyFrameSource;
using IceCores::DummyFrameSink;
using IceCores::Tray;

BOOST_AUTO_TEST_CASE(instantiation){
  EmptyFrameSource source;
  DummyFrameSink sink;

  Tray<EmptyFrameSource, DummyFrameSink> tray(source, sink);  
  
}
