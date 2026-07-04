file(GLOB_RECURSE TEST_SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
add_executable(test_runner ${TEST_SOURCES})
target_link_libraries(test_runner PRIVATE raytracer_lib gtest gtest_main)

gtest_discover_tests(test_runner)
