# CMakeList.txt: 04_vcpkg 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)

if (MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /utf-8")
endif()
if (UNIX)
	set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE BOOL "Whether to export compile commands for the project")
endif()
set(CMAKE_CXX_STANDARD 17 CACHE STRING "The C++ standard to use")
set(CMAKE_CXX_STANDARD_REQUIRED True CACHE BOOL "Whether the C++ standard is required")
set(CMAKE_CXX_EXTENSIONS False CACHE BOOL "Whether to use compiler-specific C++ extensions")
set(VCPKG_TARGET_TRIPLET "x64-linux" CACHE STRING "Vcpkg target triplet")

project ("04_vcpkg")

find_package(glfw3 CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)

add_subdirectory(3rd/glad)

# 将源代码添加到此项目的可执行文件。
add_executable (
	${PROJECT_NAME}
	src/main.cpp
)

target_link_libraries(
	${PROJECT_NAME}
	PRIVATE
	glad
	glfw
	spdlog::spdlog
)

install(
    TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)