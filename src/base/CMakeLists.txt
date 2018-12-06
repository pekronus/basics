cmake_minimum_required(VERSION 2.8.9)
project(base)
set(DEV_ROOT $ENV{HOME}/dev)
message("dev root is ${DEV_ROOT}")
set(CMAKE_BUILD_TYPE Debug)
#Bring the headers into the project
include_directories("${DEV_ROOT}/basics/include")

set ( PROJECT_LINK_LIBS libbase.a )

#However, the file(GLOB...) allows for wildcard additions:
file(GLOB SOURCES "${DEV_ROOT}/basics/src/base/*.cpp")

add_library(base STATIC ${SOURCES})

add_executable(PKDate.test "${DEV_ROOT}/basics/src/base/test/PKDate.test.cpp")
target_link_libraries(PKDate.test base)
add_executable(Matrix.test "${DEV_ROOT}/basics/src/base/test/Matrix.test.cpp")
target_link_libraries(Matrix.test base)
