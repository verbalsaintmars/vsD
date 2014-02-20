# ******************************
# Copyleft 2014 Verbalsaint
# ******************************

# Directories
SET(INCLUDE_PATH "${PROJECT_SOURCE_DIR}/include" )
SET(PUBLIC_HEADER_PATH "${PROJECT_SOURCE_DIR}/public" )
#SET(PROJECT_BINARY_DIR "${PROJECT_SOURCE_DIR}/build" )
SET(PROJECT_CMAKE_FILES "${PROJECT_SOURCE_DIR}/cmakefiles")


# Build release type parameters
# cmake -DCMAKE_BUILD_TYPE=Release
# cmake -DCMAKE_BUILD_TYPE=Debug
# Possible values are empty, Debug, Release, RelWithDebInfo and MinSizeRel.
# http://stackoverflow.com/questions/7724569/debug-vs-release-in-cmake
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -O3")

# For Build Directory
SET(BIN_DIR "${PROJECT_BINARY_DIR}/bin")
SET(TEST_BIN_DIR "${PROJECT_BINARY_DIR}/test_bin")

# For Dynamic modules
SET(MODULES_PATH "modules")

# RPATH
SET(CMAKE_SKIP_BUILD_RPATH  FALSE)
SET(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)
SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH FALSE)

# http://www.cmake.org/pipermail/cmake/2008-January/019290.html
# SET (CMAKE_EXE_LINKER_FLAGS
#     "${CMAKE_EXE_LINKER_FLAGS} -Wl,-rpath,'$$ORIGIN/../xxx/'" )

# SET (CMAKE_SHARED_LINKER_FLAGS
#     "${CMAKE_SHARED_LINKER_FLAGS} -Wl,-rpath,'$ORIGIN/../xxx'" )


# the RPATH to be used when installing, but only if it's not a system directory
#LIST(FIND CMAKE_PLATFORM_IMPLICIT_LINK_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/lib" isSystemDir)
#IF("${isSystemDir}" STREQUAL "-1")
#   SET(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
#ENDIF("${isSystemDir}" STREQUAL "-1")

# Install
# make DESTDIR=/home/john install
SET(CMAKE_INSTALL_PREFIX "/tmp/vsD")
#SET(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/dynlibrary")
