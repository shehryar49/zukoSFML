cmake_minimum_required(VERSION 3.16.3 FATAL_ERROR)
project(sfml)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_SHARED_LIBRARY_PREFIX "")
if(UNIX)
  link_directories(/opt/zuko/lib)
else()
  link_directories(C:\\zuko\\lib)
endif()
add_library(sfml SHARED sfml.cpp sfml.h)
find_package(SFML REQUIRED system window graphics)

target_link_libraries(sfml PUBLIC sfml-graphics)
target_link_libraries(sfml PUBLIC sfml-system)
target_link_libraries(sfml PUBLIC sfml-window)
target_link_libraries(sfml PRIVATE zapi)
