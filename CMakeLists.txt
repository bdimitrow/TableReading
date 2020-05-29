cmake_minimum_required(VERSION 3.16)
project(TableReading)

set(CMAKE_CXX_STANDARD 20)

add_executable(TableReading main.cpp application.h matrix.cpp matrix.h formula.cpp formula.h application.cpp stringUtils.h)