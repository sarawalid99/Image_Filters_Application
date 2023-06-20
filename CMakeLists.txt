cmake_minimum_required(VERSION 3.25)
project(Image_Filters_App)

set(CMAKE_CXX_STANDARD 14)

add_executable(Image_Filters_App
        bmplib.h bmplib.cpp Gray_Filters.cpp RGB_Filters.cpp)
