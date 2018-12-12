cmake_minimum_required(VERSION 2.8.9)
project(ml)
set(DEV_ROOT $ENV{HOME}/dev)
set(LIBNAME ml)
message("dev root is ${DEV_ROOT}")
set(CMAKE_BUILD_TYPE Debug)
#Bring the headers into the project
include_directories("${DEV_ROOT}/basics/include")
set ( PROJECT_LINK_LIBS lib${LIBNAME}.a )

#However, the file(GLOB...) allows for wildcard additions:
file(GLOB SOURCES "${DEV_ROOT}/basics/src/${LIBNAME}/*.cpp")

add_library(${LIBNAME} STATIC ${SOURCES})

add_executable(NNetFeedForward.test "${DEV_ROOT}/basics/src/ml/test/NNetFeedForward.test.cpp")
target_link_libraries(NNetFeedForward.test base ml)

