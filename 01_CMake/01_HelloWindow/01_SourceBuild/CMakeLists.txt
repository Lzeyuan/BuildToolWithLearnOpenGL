cmake_minimum_required (VERSION 3.22)

set(CMAKE_CXX_STANDARD 17 CACHE STRING "The C++ standard to use")
set(CMAKE_CXX_STANDARD_REQUIRED True CACHE BOOL "Whether the C++ standard is required")
set(CMAKE_CXX_EXTENSIONS False CACHE BOOL "Whether to use compiler-specific C++ extensions")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE BOOL "Whether to export compile commands for the project")

project ("01_SourceBuild")

add_executable (
	${PROJECT_NAME} 
	src/main.cpp
)

add_subdirectory(3rd/glad)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
option(GLFW_BUILD_EXAMPLES "Build the GLFW example programs" OFF)
option(GLFW_BUILD_TESTS "Build the GLFW test programs" OFF)
option(GLFW_BUILD_DOCS "Build the GLFW documentation" OFF)
option(GLFW_INSTALL "Generate installation target" OFF)
add_subdirectory(3rd/glfw-3.4)

target_link_libraries(
	${PROJECT_NAME}
	PRIVATE
	glad
	glfw
)
