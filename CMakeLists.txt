cmake_minimum_required(VERSION 3.17)
project(hh-timer)

set(CMAKE_CXX_STANDARD 20)

find_package (Threads REQUIRED)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM REQUIRED gtkmm-3.0)
include_directories(${GTKMM_INCLUDE_DIRS})
link_directories(${GTKMM_LIBRARY_DIRS})
add_definitions(${GTKMM_CFLAGS_OTHER})

add_executable(hh-timer src/timer.h src/timer.cc src/main.cc src/window.h src/window.cc src/worker.h src/worker.cc)
target_link_libraries(hh-timer ${CMAKE_THREAD_LIBS_INIT} ${GTKMM_LIBRARIES})

add_executable(hh-timer-test test/main.cc)
target_link_libraries(hh-timer-test ${CMAKE_THREAD_LIBS_INIT} ${GTKMM_LIBRARIES})