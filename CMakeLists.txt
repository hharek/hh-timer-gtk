cmake_minimum_required(VERSION 3.17)
project(hh-timer)

set(CMAKE_CXX_STANDARD 14)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})

add_definitions(${GTK3_CFLAGS_OTHER})

add_executable(hh-timer src/main.cpp)

target_link_libraries(hh-timer ${GTK3_LIBRARIES})