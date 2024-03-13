cmake_minimum_required(VERSION 3.27)
project(Encryption)

set(CMAKE_CXX_STANDARD 17)

# Add platform-specific settings
if (WIN32)
    # Additional settings for Windows
    set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++ -static")
endif()

add_executable(Encryption main.cpp)
