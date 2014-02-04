cmake_minimum_required(VERSION 2.8)

project (zia)
set(CMAKE_BUILD_TYPE Release)

add_definitions(-DDllApimeal)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/includes)

set(SDIR sources/)
set(SOURCES ${SDIR}main.cpp ${SDIR}ModuleLoader.cpp ${SDIR}Server.cpp ${SDIR}ConfParser.cpp ${SDIR}Logger.cpp
  ${SDIR}ConnexionAttente.cpp ${SDIR}ConnexionClient.cpp ${SDIR}Thread.cpp ${SDIR}HttpResponse.cpp
  ${SDIR}HttpRequest.cpp ${SDIR}pipeline.cpp)

add_executable(zia ${SOURCES})
add_executable(launcher ${SDIR}launcher.cpp)

if (UNIX)
  target_link_libraries(zia dl)
  target_link_libraries(zia pthread)
  target_link_libraries(zia ssl)
  target_link_libraries(zia crypto)
endif()

add_subdirectory(modules/mod_dir/)
add_subdirectory(modules/mod_error/)
add_subdirectory(modules/mod_phpcgi/)
add_subdirectory(modules/mod_ssl/)
