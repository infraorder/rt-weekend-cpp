cmake_minimum_required(VERSION 3.28)
project(rt_weekend_1_cpp)

set(CMAKE_CXX_STANDARD 17)

add_executable(rt_weekend_1_cpp src/main.cpp
        src/vec3.h
        src/color.h
        src/ray.h
)
