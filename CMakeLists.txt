cmake_minimum_required(VERSION 3.10)
project(sproutsh)

set(CMAKE_CXX_STANDARD 17)

add_executable(sproutsh.exe src/main.cpp src/shell.cpp src/parser.cpp src/builtins.cpp src/executor.cpp src/history.cpp)