# ******************************
# Copyleft 2014 Verbalsaint
# ******************************
cmake_minimum_required(VERSION 2.8)

add_executable(vsD_dl test.cpp)

set_property(TARGET vsD_dl
   PROPERTY RUNTIME_OUTPUT_DIRECTORY "${TEST_BIN_DIR}")

target_link_libraries(vsD_dl "-ldl")

set_target_properties(vsD_dl PROPERTIES LINK_FLAGS
   "${CMAKE_SHARED_LINKER_FLAGS} -Wl,-rpath,'$ORIGIN'/${MODULES_PATH}")

target_include_directories(vsD_dl PRIVATE PRIVATE "${CMAKE_SOURCE_DIR}/include"
   "${CMAKE_SOURCE_DIR}/public")



# Test Modules
add_library(foo SHARED libfoo.cpp)

set_property(TARGET foo
   PROPERTY LIBRARY_OUTPUT_DIRECTORY "${TEST_BIN_DIR}/${MODULES_PATH}")

target_include_directories(foo PRIVATE "${CMAKE_SOURCE_DIR}/include" PUBLIC
   "${CMAKE_SOURCE_DIR}/public")

