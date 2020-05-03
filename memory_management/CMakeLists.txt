cmake_minimum_required(VERSION 2.8)

project(fastGaussianBlur)

SET(CMAKE_BUILD_TYPE Release)

find_package(OpenCV)
if(NOT OpenCV_FOUND)
    message(FATAL_ERROR "OpenCV not found.")
 endif()

add_executable(fastGaussianBlur main.cpp)
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
