cmake_minimum_required(VERSION 3.20)
project(learn-ray-tracing VERSION 1.0.0 LANGUAGES CXX)

# C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# Third-party libraries
add_subdirectory(3rd)

# Source
file(GLOB_RECURSE LIB_SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
# Separate main.cpp from library sources
list(FILTER LIB_SOURCES EXCLUDE REGEX "main\\.cpp$")
add_library(raytracer_lib ${LIB_SOURCES})
target_include_directories(raytracer_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(raytracer_lib PUBLIC glm spdlog stb)

add_executable(ray_tracer ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)
target_link_libraries(ray_tracer PRIVATE raytracer_lib)

# Tests
enable_testing()
include(GoogleTest)
add_subdirectory(tests)
