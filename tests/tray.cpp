#define BOOST_TEST_MODULE My_Test
#include <boost/test/included/unit_test.hpp>

#include <ice_cores/tray.hpp>

using IceCores::EmptyFrameSource;
using IceCores::DummyFrameSink;
using IceCores::Tray;

BOOST_AUTO_TEST_CASE(instantiation){
  EmptyFrameSource source;
  DummyFrameSink sink;

  Tray<EmptyFrameSource, DummyFrameSink> tray(std::move(source), sink);

}

BOOST_AUTO_TEST_CASE(execute_pipelines){
  unsigned n_frames{42};
  EmptyFrameSource source(n_frames);
  DummyFrameSink sink;

  Tray<EmptyFrameSource, DummyFrameSink> tray(std::move(source), sink);

  tray.execute_pipelines();

}
