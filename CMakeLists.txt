cmake_minimum_required(VERSION 3.30)
project(ESTRUCTURA_DATOS C)


set(CMAKE_C_STANDARD 90)

add_executable(ESTRUCTURA_DATOS main.c)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")
