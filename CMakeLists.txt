cmake_minimum_required(VERSION 3.0)

project(libbuildgen)

file(GLOB SOURCES src/*.c)

add_library(buildgen ${SOURCES})

add_executable(testbuild tests/build.c)
