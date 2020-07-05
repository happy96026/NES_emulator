cmake_minimum_required(VERSION 3.13)
project(NES_emulator)

set(CMAKE_CXX_STANDARD 17)

add_executable(NES_emulator main.cpp Bus.cpp Bus.h C6502.cpp C6502.h)