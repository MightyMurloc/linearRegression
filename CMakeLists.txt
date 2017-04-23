cmake_minimum_required(VERSION 2.8)
project(pf162a01)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp commonLib.cpp commonLib.h linearRegression.cpp linearRegression.h)
add_executable(pf162a01 ${SOURCE_FILES})