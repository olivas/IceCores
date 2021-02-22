
include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(pipeline_example
  ${CMAKE_SOURCE_DIR}/src/examples/pipeline_example.cpp)
target_link_libraries(pipeline_example pthread icecores)

add_executable(frame_race
  ${CMAKE_SOURCE_DIR}/src/examples/frame_read_write_race.cpp)
target_link_libraries(frame_race pthread icecores)

  
