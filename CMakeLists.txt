cmake_minimum_required(VERSION 3.23)
project(SOS)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(SOS
        dataStructure.h
        DiskManager.h
        main.cpp
        Operations.h)
