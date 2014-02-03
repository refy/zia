cmake_minimum_required(VERSION 2.8)

project (mod_error)
set(CMAKE_BUILD_TYPE Release)

add_definitions(-DDllApimeal)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../includes)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/includes)

if(CMAKE_COMPILER_IS_GNUCXX)
  add_definitions(-std=gnu++0x)
endif()

add_library(mod_error SHARED sources/mod_error.cpp)
