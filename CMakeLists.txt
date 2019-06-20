cmake_minimum_required(VERSION 2.8.3)
project(BWString)

add_compile_options(-std=c++14)

#find_package

include_directories(
        include
)

add_executable(BWString src/BWString.cpp)

#target_link_libraries(BWString ${PROJECT_NAME})