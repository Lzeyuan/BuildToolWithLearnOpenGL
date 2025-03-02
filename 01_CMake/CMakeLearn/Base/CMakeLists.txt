cmake_minimum_required(VERSION 3.25)

project(Base VERSION 1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(
    ${PROJECT_NAME}
    STATIC
    stdafx.cpp
    shader.h
    camera.h
)

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
    "/"
)

target_precompile_headers(
    ${PROJECT_NAME}
    PUBLIC
    stdafx.h
)

find_package(glfw3 CONFIG REQUIRED)

target_link_libraries(
    ${PROJECT_NAME}
    PUBLIC
    glfw
    glad
    glm
    stb_image
)