cmake_minimum_required(VERSION 3.29)
project(a3_demo)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(a3_demo
    main.cpp
    Map.cpp
    Map.h
    Queue.cpp
    Queue.h
    RoutePlanner.cpp
    RoutePlanner.h
    Stack.cpp
    Stack.h)
