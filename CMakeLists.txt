cmake_minimum_required(VERSION 3.15)
project(Chess CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(chess
    src/main.cpp 
    src/piece.cpp
    src/board.cpp
)

target_include_directories(chess PRIVATE src)