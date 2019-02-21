include(CTest)
enable_testing()

include(CodeCoverage)

set(GTEST_PATH ${CMAKE_SOURCE_DIR}/submodules)

set(INSTALL_GTEST OFF CACHE BOOL "Don't install gtest.")
set(INSTALL_GMOCK OFF CACHE BOOL "Don't install gmock.")
set(BUILD_GMOCK OFF CACHE BOOL "Don't build gmock.")
set(BUILD_GTEST ON CACHE BOOL "Build gtest.")

include(CMakeDependentOption)
include(GNUInstallDirs)

option(BUILD_GTEST "Builds the googletest subproject" OFF)
#Note that googlemock target already builds googletest
option(BUILD_GMOCK "Builds the googlemock subproject" ON)

cmake_dependent_option(INSTALL_GTEST
  "Enable installation of googletest. (Projects embedding googletest may want to turn this OFF.)" ON
  "BUILD_GTEST OR BUILD_GMOCK" OFF
  )

cmake_dependent_option(INSTALL_GMOCK
  "Enable installation of googlemock. (Projects embedding googlemock may want to turn this OFF.)" ON
  "BUILD_GMOCK" OFF
  )

if(BUILD_GMOCK)
  add_subdirectory( ${GTEST_PATH}/googletest/googlemock )
elseif(BUILD_GTEST)
  add_subdirectory( ${GTEST_PATH}/googletest/googletest )
endif()

include_directories(${GTEST_PATH}/googletest/googletest/include)

# This creates an executable with name <executable_name>
# and links to the library <library_name>
function(add_unit_test library_name test_source)
  add_executable(${library_name}_${test_source}
    ${CMAKE_SOURCE_DIR}/tests/${test_source}.cpp
    ${CMAKE_SOURCE_DIR}/tests/main.cpp
    )
  target_link_libraries(${library_name}_${test_source} gtest_main ${library_name})
  add_test(NAME ${library_name}_${test_source} COMMAND ${library_name}_${test_source})     
endfunction()

add_unit_test(icecores tray)

# the following lives in modules/CodeCoverage
append_coverage_compiler_flags()
setup_target_for_coverage(
  NAME icecores_coverage
  EXECUTABLE sudo ctest -j 3
  )
