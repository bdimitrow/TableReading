cmake_minimum_required(VERSION 3.16)
project(TableReading)

set(CMAKE_CXX_STANDARD 20)

add_executable(TableReading main.cpp commands.h readFile.h dataTypes.h CellClass.h DynamicArray.h heterogeneousContainer.h CellStringClass.h application.h)