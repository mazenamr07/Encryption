cmake_minimum_required(VERSION 3.27)
project(Encryption)

set(CMAKE_CXX_STANDARD 17)

add_executable(Encryption main.cpp)

set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++ -static")
