cmake_minimum_required(VERSION 3.0)

project(nova)


if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel." FORCE)
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Wextra -fno-rtti -fno-exceptions -fstrict-aliasing -fomit-frame-pointer")

configure_file(
    "${CMAKE_SOURCE_DIR}/src/config.h.in"
    "${CMAKE_BINARY_DIR}/include/nova/config.h"
)

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(nova ${SOURCES})
target_include_directories(
    nova
    PUBLIC
    "${CMAKE_SOURCE_DIR}/include"
    "${CMAKE_BINARY_DIR}/include"
    PRIVATE
    "${CMAKE_SOURCE_DIR}/src"
)

install(TARGETS nova RUNTIME DESTINATION bin)
install(DIRECTORY "${CMAKE_SOURCE_DIR}/include/nova" DESTINATION include)
install(FILES "${CMAKE_BINARY_DIR}/include/nova/config.h" DESTINATION include/nova)
