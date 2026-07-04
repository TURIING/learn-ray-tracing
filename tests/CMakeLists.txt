file(GLOB_RECURSE TEST_SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
add_executable(test_image ${TEST_SOURCES})
target_link_libraries(test_image PRIVATE image gtest gtest_main)

gtest_discover_tests(test_image)
