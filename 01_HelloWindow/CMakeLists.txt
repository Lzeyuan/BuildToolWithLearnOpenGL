cmake_minimum_required (VERSION 3.8)

project ("01_HelloWindow")

add_executable (
	01_HelloWindow 
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
	01_HelloWindow
	PRIVATE
	glad
	glfw
	opengl32
)