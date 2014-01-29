cmake_minimum_required(VERSION 2.8)

project (zia)
set(CMAKE_BUILD_TYPE Release)

add_definitions(-DDllApimeal)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/includes)

set(SOURCES_DIR sources/)
set(SOURCES ${SOURCES_DIR}main.cpp ${SOURCES_DIR}ModuleLoader.cpp ${SOURCES_DIR}Server.cpp ${SOURCES_DIR}ConfParser.cpp ${SOURCES_DIR}Logger.cpp)

add_executable(zia ${SOURCES})

if (UNIX)
  target_link_libraries(zia dl)
endif()