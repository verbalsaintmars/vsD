# ******************************
# Copyleft 2014 Verbalsaint
# ******************************
cmake_minimum_required(VERSION 2.8)

add_executable(vsD_child child.cpp)

set_property(TARGET vsD_child
   PROPERTY RUNTIME_OUTPUT_DIRECTORY "${TEST_BIN_DIR}")


target_include_directories(vsD_child PRIVATE "${CMAKE_SOURCE_DIR}/include")

target_link_libraries(vsD_child "-lgflags")
