
include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(first_example ${CMAKE_SOURCE_DIR}/src/examples/first_example.cpp)
target_link_libraries(first_example icecores)

add_executable(threads_are_not_copyable
  ${CMAKE_SOURCE_DIR}/src/examples/threads_are_not_copyable.cpp)
target_link_libraries(threads_are_not_copyable pthread)
  
  
