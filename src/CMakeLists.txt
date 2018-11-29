cmake_minimum_required(VERSION 2.8.9)
project(ml)
set(DEV_ROOT $ENV{HOME}/dev)
message("dev root is ${DEV_ROOT}")
set(CMAKE_BUILD_TYPE Debug)
#Bring the headers into the project
include_directories("${DEV_ROOT}/basics/include")

add_subdirectory(base)
add_subdirectory(ml)


