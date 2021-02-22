include(CTest)
enable_testing()

# This creates an executable with name <library
# and links to the library <library_name>
function(add_unit_test library_name test_source)
  set(TEST_NAME ${library_name}_${test_source})
  add_executable(${TEST_NAME}
    ${CMAKE_SOURCE_DIR}/tests/${test_source}.cpp
    )
  target_link_libraries(${TEST_NAME} ${library_name})
  add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endfunction()

# Add more unit tests here
# They'll all likely link to the icecores library
# The second argument is source <name>.cpp in the tests directory
add_unit_test(icecores tray)
add_unit_test(icecores lock_free_queue)
