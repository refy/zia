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

add_subdirectory(modules/CGIModule/)
add_subdirectory(modules/PreParseRequest/)
add_subdirectory(modules/PreSendRequest/)
add_subdirectory(modules/PostGenerateResponse/)
add_subdirectory(modules/PreConnexion/)
add_subdirectory(modules/ContentModule/)
add_subdirectory(modules/PostConnexion/)
add_subdirectory(modules/PostParseRequest/)