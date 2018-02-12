cmake_minimum_required(VERSION 3.5)
project(worm)

set(CMAKE_BUILD_TYPE RelWithDebInfo)
set(CMAKE_CXX_STANDARD 11)
set(THREADS_PREFER_PTHREAD_FLAG ON)

file(GLOB SOURCES "*.cc")
add_executable(worm ${SOURCES})

# pthread library
find_package(Threads REQUIRED)

# ncurses library
find_path(NCURSES_INCLUDE_DIR ncurses.h)
find_library(NCURSES_LIBRARY ncurses)

# glog library
find_path(GLOG_INCLUDE_DIR glog/logging.h)
find_library(GLOG_LIBRARY glog)

target_include_directories(worm PUBLIC ${NCURSES_INCLUDE_DIR} ${GLOG_INCLUDE_DIR})
target_link_libraries(worm PUBLIC ${NCURSES_LIBRARY} ${GLOG_LIBRARY} Threads::Threads)
