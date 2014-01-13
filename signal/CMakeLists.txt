# ******************************
# Copyleft 2014 Verbalsaint
# ******************************
cmake_minimum_required(VERSION 2.8)

add_executable(vsD_signal test.cpp)

set_property(TARGET vsD_signal
   PROPERTY RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/test_bin")

# install(TARGETS vsD_signal DESTINATION /tmp)
