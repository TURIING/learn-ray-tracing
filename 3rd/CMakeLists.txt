# stb — header-only image library
add_library(stb INTERFACE)
target_include_directories(stb INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/stb)

# Google Test
add_subdirectory(googletest EXCLUDE_FROM_ALL)
