cmake_minimum_required(VERSION 2.8)

project (mod_ssl)
set(CMAKE_BUILD_TYPE Release)

add_definitions(-DDllApimeal)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../includes)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/includes)

if(CMAKE_COMPILER_IS_GNUCXX)
  add_definitions(-std=gnu++0x)
endif()

if (UNIX)
  LINK_LIBRARIES(ssl)
  LINK_LIBRARIES(crypto)
endif()

add_library(mod_ssl SHARED sources/mod_ssl.cpp)
