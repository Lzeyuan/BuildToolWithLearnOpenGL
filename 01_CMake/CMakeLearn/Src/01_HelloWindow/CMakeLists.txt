cmake_minimum_required(VERSION 3.25)

project(01_HelloWindow VERSION 1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(
    ${PROJECT_NAME}
    main.cpp
)

target_precompile_headers(
    ${PROJECT_NAME}
    REUSE_FROM
    Base
)

target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE
    Base
)