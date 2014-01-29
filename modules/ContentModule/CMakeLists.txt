cmake_minimum_required(VERSION 2.8)

project (ContentModule)
set(CMAKE_BUILD_TYPE Release)

add_definitions(-DDllApimeal)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../includes)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/includes)

add_library(ContentModule SHARED sources/ContentModule.cpp)