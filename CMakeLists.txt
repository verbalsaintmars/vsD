# ******************************
# Copyleft 2014 Verbalsaint
# ******************************

# TODO main make
# TODO test make
# TODO different bin location
# TODO install
# TODO cpack
# TODO ctest
cmake_minimum_required (VERSION 2.8.9)
project (vsD CXX)

# includes
include("${PROJECT_SOURCE_DIR}/cmakefiles/variables.cmake")
include("${PROJECT_CMAKE_FILES}/cpp11.cmake")
include("${PROJECT_CMAKE_FILES}/create_dir.cmake")
include("${PROJECT_CMAKE_FILES}/includedir.cmake")

# sub dirs to build
add_subdirectory(dbus)
#add_subdirectory(child)
# add_subdirectory(dl)
# add_subdirectory(signal)
# add_subdirectory(daemon)

# main program
#add_executable (vsD test.cpp)
#set_property(TARGET vsD
#   PROPERTY RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")
