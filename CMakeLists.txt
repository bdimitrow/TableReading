cmake_minimum_required(VERSION 3.16)
project(TableReading)

set(CMAKE_CXX_STANDARD 20)

add_executable(TableReading main.cpp commands.h readFile.h dataTypes.h templateClass.h CellClass.h file.h RowClass.h DynamicArray.h heterogeneousContainer.h CellStringClass.h)