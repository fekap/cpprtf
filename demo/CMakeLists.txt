project(demo)
cmake_minimum_required(VERSION 2.8)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

file(GLOB SRC_LIST "*.h" "*.cpp")
INCLUDE_DIRECTORIES(../boost)
add_library(${PROJECT_NAME} SHARED ${SRC_LIST})
target_link_libraries(${PROJECT_NAME} boost_regex)