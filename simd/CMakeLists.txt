cmake_minimum_required(VERSION 2.8)

project(fastGaussianBlur)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -std=c++11 -funroll-loops -Ofast")

find_package(OpenCV)

if(NOT OpenCV_FOUND)
    message(FATAL_ERROR "OpenCV not found.")
 endif()

add_executable(fastGaussianBlur main.cpp)
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
