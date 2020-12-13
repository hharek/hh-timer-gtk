cmake_minimum_required(VERSION 3.17)
project(hh-timer)

set(CMAKE_CXX_STANDARD 14)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM REQUIRED gtkmm-3.0)

include_directories(${GTKMM_INCLUDE_DIRS})
link_directories(${GTKMM_LIBRARY_DIRS})

add_definitions(${GTKMM_CFLAGS_OTHER})

add_executable(hh-timer src/main.cpp)
target_link_libraries(hh-timer ${GTKMM_LIBRARIES})