cmake_minimum_required (VERSION 3.19)

# Only Linux， 在CMakeUserPreset.json设置
# set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib" CACHE STRING "Dynamic library find path")
set(CMAKE_CXX_STANDARD 17 CACHE STRING "The C++ standard to use")
set(CMAKE_CXX_STANDARD_REQUIRED True CACHE BOOL "Whether the C++ standard is required")
set(CMAKE_CXX_EXTENSIONS False CACHE BOOL "Whether to use compiler-specific C++ extensions")
# 只有构建工具是makefile或者Ninja才生效。
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE BOOL "Whether to export compile commands for the project")

project ("02_Introduction")

find_package(glfw3 CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)

add_subdirectory(3rd/glad)
add_subdirectory(3rd/glm)
add_subdirectory(3rd/stb_image)

# 将源代码添加到此项目的可执行文件。
add_executable (
	${PROJECT_NAME}
	src/main.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE
	glad
	glfw
	glm
	stb_image
	spdlog::spdlog
)

target_include_directories(${PROJECT_NAME} PRIVATE  
	src
)

target_precompile_headers(${PROJECT_NAME} PRIVATE 
	src/stdafx.hpp
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/resources ${CMAKE_BINARY_DIR}/resources
    COMMENT "Copying resources directory to build directory..."
)

install(
    TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
)