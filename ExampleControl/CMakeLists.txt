cmake_minimum_required(VERSION 3.0.0)
project(ExampleControl)

add_executable(${PROJECT_NAME} ExampleControl.cpp)

target_link_libraries(${PROJECT_NAME} KeyRemapper)

include(FetchContent)

FetchContent_Declare(json
  URL https://github.com/nlohmann/json/releases/download/v3.10.5/json.tar.xz
)

FetchContent_GetProperties(json)
if(NOT json_POPULATED)
  FetchContent_Populate(json)
  add_subdirectory(${json_SOURCE_DIR} ${json_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

target_link_libraries(${PROJECT_NAME} nlohmann_json::nlohmann_json)