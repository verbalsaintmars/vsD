# ******************************
# Copyleft 2014 Verbalsaint
# ******************************
cmake_minimum_required(VERSION 2.8)

add_executable(vsD vsd.cpp)

set_property(TARGET vsD
   PROPERTY RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/test_bin")

target_include_directories(foo PRIVATE "${CMAKE_SOURCE_DIR}/include" PUBLIC
   "${CMAKE_SOURCE_DIR}/public")
