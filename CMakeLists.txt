cmake_minimum_required(VERSION 3.11)

project(raytracer
  VERSION 1.0.0
  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

add_executable(raytracer src/main.cpp src/camera.cpp src/matrix_operations.cpp
                         src/vector.cpp)

target_include_directories(raytracer PUBLIC src)

