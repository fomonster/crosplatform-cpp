# /*
# (c) 2014 +++ Filip Stoklas, aka FipS, http://www.4FipS.com +++
# THIS CODE IS FREE - LICENSED UNDER THE MIT LICENSE
# ARTICLE URL: http://forums.4fips.com/viewtopic.php?f=3&t=1201
# */

cmake_minimum_required(VERSION 2.8)
add_definitions("-std=c++11")
project(hello_triangle)
file(GLOB sources *.cpp ../../src/*.cpp)

#include_directories(${ROOT_SOURCE_DIR}../../src/)
#add_library(lib STATIC ../../src/)
#set(SOURCES app.cpp app.h)
add_executable(hello_triangle ${sources})
