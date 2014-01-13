# ******************************
# Copyleft 2014 Verbalsaint
# ******************************
# enable c++11/1y build
include(CheckCXXCompilerFlag)


macro(ChkCompilerVer)
   if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
       # require at least gcc 4.8
      if (CMAKE_CXX_COMPILER_VERSION VERSION_GREATER 4.8.0)
         set(COMPILER_VERSION_CHK 1)
      endif()

   elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
       # require at least clang 3.2
      if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 3.3)
         set(COMPILER_VERSION_CHK 1)
      endif()

   else()
       message(WARNING "Unsupported compiler! gcc > 4.8.0 || clang > 3.3")
   endif()
endmacro(ChkCompilerVer)


macro(SETCXX11FLAG)

   ChkCompilerVer()

   CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
   CHECK_CXX_COMPILER_FLAG("-std=c++1y" COMPILER_SUPPORTS_CXX1Y)

   if(${COMPILER_VERSION_CHK})
      if(COMPILER_SUPPORTS_CXX1Y)
         list(INSERT CMAKE_CXX_FLAGS 0 "-std=c++1y")

      elseif(COMPILER_SUPPORTS_CXX11)
         list(INSERT CMAKE_CXX_FLAGS 0 "-std=c++11")

      else()
         message(STATUS "${CMAKE_CXX_COMPILER} has no C++11 support.")
      endif()
   endif()
endmacro(SETCXX11FLAG)

SETCXX11FLAG()
