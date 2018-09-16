cmake_minimum_required(VERSION 3.7)
project(quadratic_equation_solver)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
add_subdirectory(googletest)
include_directories(googletest/googletest/include)
include_directories(googletest/googlemock/include)

set(SOURCE_FILES Tests.cpp quadratic_equation_solver.h)
add_executable(quadratic_equation_solver ${SOURCE_FILES})

target_link_libraries(quadratic_equation_solver gtest gtest_main)
