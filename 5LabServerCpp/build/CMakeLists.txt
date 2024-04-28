cmake_minimum_required(VERSION 3.13)
project(visualizationGraph)
set(CMAKE_CXX_STANDARD 17)

include_directories("include/")

add_executable(main 
    ../src/main.cpp
    ../src/deleteFile.cpp
    ../src/editFile.cpp
    ../src/handleClient.cpp
    ../src/logger.cpp
    ../src/sendErrorResponse.cpp
    ../src/sendFile.cpp
    ../src/sendFileList.cpp
    ../src/server.cpp
    ../src/uploadFile.cpp
    ../src/urlDecode.cpp
)
