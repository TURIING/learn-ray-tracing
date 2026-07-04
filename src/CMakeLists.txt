file(GLOB_RECURSE IMAGE_SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/utils/*.cpp)
add_library(image STATIC ${IMAGE_SOURCES})
target_include_directories(image PUBLIC ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(image PUBLIC stb)

file(GLOB RAYTRACER_SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
add_executable(ray_tracer ${RAYTRACER_SOURCES})
