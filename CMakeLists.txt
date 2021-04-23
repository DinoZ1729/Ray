cmake_minimum_required(VERSION 3.11)

project(raytracer
  VERSION 1.0.0
  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

file(GLOB files_cpp "src/*.cpp")
add_executable(raytracer ${files_cpp})

target_include_directories(raytracer PUBLIC src)

