cmake_minimum_required(VERSION 3.12)
project(todo-list VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(HEADER_FILES
    headers/utils.hpp
    headers/task.hpp
    headers/task_manager.hpp
    headers/task_cli.hpp
)

set(SOURCE_FILES
    src/utils.cpp
    src/task_manager.cpp
    src/task_cli.cpp
    src/main.cpp
)

add_executable(todo-list ${SOURCE_FILES} ${HEADER_FILES})

target_include_directories(todo-list PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/headers/)
