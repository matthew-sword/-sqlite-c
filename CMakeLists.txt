cmake_minimum_required(VERSION 3.8)
project(sqlite_C)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c sqlite3.c sqlite3.h)
add_executable(sqlite_C ${SOURCE_FILES})