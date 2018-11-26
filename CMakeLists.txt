cmake_minimum_required(VERSION 2.8.9)
project(basics)
set(CMAKE_BUILD_TYPE Debug)
#Bring the headers, such as Student.h into the project
include_directories(include)

set ( PROJECT_LINK_LIBS libbasics.a )

#However, the file(GLOB...) allows for wildcard additions:
file(GLOB SOURCES "src/*.cpp")

add_library(basics STATIC ${SOURCES})
add_executable(PKDate.test ${SOURCES})

