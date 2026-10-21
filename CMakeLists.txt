cmake_minimum_required(VERSION 3.20)
project(Order_Book CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(carnet Main.cpp orderbook.cpp)
target_compile_options(carnet PRIVATE -Wall -Wextra)