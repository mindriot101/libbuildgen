cmake_minimum_required(VERSION 3.0)

set(CMAKE_C_STANDARD 11)

project(libbuildgen)

file(GLOB SOURCES src/*.c)
file(GLOB HEADERS include/*.h)

add_library(buildgen ${SOURCES} ${HEADERS})
target_include_directories(buildgen PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(testbuild tests/build.c)
target_include_directories(testbuild PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(testbuild buildgen)

add_dependencies(testbuild buildgen)
add_custom_target(run ./testbuild DEPENDS testbuild)
