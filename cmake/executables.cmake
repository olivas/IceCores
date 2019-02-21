
include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(first_example ${CMAKE_SOURCE_DIR}/src/examples/first_example.cpp)
target_link_libraries(first_example icecores)
  
  
