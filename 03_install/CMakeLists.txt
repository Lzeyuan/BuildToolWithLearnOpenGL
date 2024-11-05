cmake_minimum_required (VERSION 3.8)

project ("03_install")
# 设置 C++ 编译器选项以启用 UTF-8 编码
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /utf-8")

set(CMAKE_PREFIX_PATH E:\\projects\\LearnCMakeWithOpenGL\\03_install\\mock_install\\x64-Debug\\lib\\cmake)

find_package(glfw3 CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)

add_executable (
    ${PROJECT_NAME} 
    src/main.cpp
)

add_subdirectory(3rd/glad)

target_include_directories(
    ${PROJECT_NAME} 
    PRIVATE
)

target_link_libraries(
    ${PROJECT_NAME} 
    PRIVATE
    glad
    glfw
    opengl32
    spdlog::spdlog
)

message("glfw3_LIBRARIES = " ${glfw3_INCLUDES})

install(
    TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    FILES ${glfw3_LIBRARIES}  DESTINATION ${CMAKE_INSTALL_LIBDIR}
)