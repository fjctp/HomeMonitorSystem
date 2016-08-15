cmake_minimum_required(VERSION 2.8)
include(cmake/functions.cmake)
set(CMAKE_CONFIGURATION_TYPES "Release;Debug;" CACHE PATH "Build type")

# define project settings
project("Surveillance System")
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

# define user's options
option(Use_OpenCL "Use OpenCL" 0)
option(Show_Windows "Use imshow function" 0)
convert2number(Use_OpenCL)   # convert from ON/OFF to 1/0
convert2number(Show_Windows) # convert from ON/OFF to 1/0

# find 3rd party library
find_package(OpenCV 3.1.0 REQUIRED)
find_package(Boost 1.60 REQUIRED)

set(OpenCV_DIR "${OpenCV_DIR}" CACHE PATH "OpenCV location")
set(Boost_INCLUDE_DIR "${Boost_INCLUDE_DIR}" CACHE PATH "BOOST include directory")
set(Boost_LIBRARY_DIR "${Boost_LIBRARY_DIR}" CACHE PATH "BOOST library directory")
set(YAML_CPP_INCLUDEDIR "${YAML_CPP_INCLUDEDIR}" CACHE PATH "YAML include directory")
set(YAML_CPP_LIBRARYDIR "${YAML_CPP_LIBRARYDIR}" CACHE PATH "YAML library directory")

# set CXX flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -DELPP_THREAD_SAFE")
#if(CMAKE_COMPILER_IS_GNUCXX)
#    message(STATUS "GCC detected, adding compile flags")
#    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
#    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused -Wuninitialized -Wdisabled-optimization")
#    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wfloat-equal -Wfloat-conversion -Wdouble-promotion")
#    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wsign-conversion")
#endif(CMAKE_COMPILER_IS_GNUCXX)

# add directories that contains source/libraries
include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIR})
include_directories(${YAML_CPP_INCLUDEDIR})
link_directories(${YAML_CPP_LIBRARYDIR})

add_subdirectory("src")

# print summary
message(STATUS "OpenCV version: ${OpenCV_VERSION}")
message(STATUS "Executable output: ${EXECUTABLE_OUTPUT_PATH}")
