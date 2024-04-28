cmake_minimum_required(VERSION 3.13)
project(visualizationGraph)
set(CMAKE_CXX_STANDARD 11)

include_directories("include/")

add_executable(main 
    ../src/main.cpp
    ../src/algorithm.cpp
    ../src/createImage.cpp
    ../src/drawingFigures.cpp
    ../src/saveFile.cpp
)