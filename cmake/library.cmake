
include_directories(${CMAKE_SOURCE_DIR}/include)

add_library(icecores SHARED 
  ${CMAKE_SOURCE_DIR}/src/ice_cores/tray.cpp
  ${CMAKE_SOURCE_DIR}/src/ice_cores/frame.cpp
  ${CMAKE_SOURCE_DIR}/src/ice_cores/modules/reader.cpp
  ${CMAKE_SOURCE_DIR}/src/ice_cores/modules/writer.cpp
  )
target_link_libraries(icecores pthread)
  
  
