cmake_minimum_required(VERSION 3.28)
project(FlappyCrow LANGUAGES CXX)

include(FetchContent)

FetchContent_Declare(ardelio
    GIT_REPOSITORY https://github.com/snakeworks/ardelio
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(ardelio)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE ardelio)
