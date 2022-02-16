cmake_minimum_required(VERSION 3.0.0)
project(ExampleControl)

add_executable(${PROJECT_NAME} ExampleControl.cpp)

target_link_libraries(${PROJECT_NAME} KeyRemapper)