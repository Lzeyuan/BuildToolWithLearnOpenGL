cmake_minimum_required (VERSION 3.15)

if (CMAKE_SYSTEM_NAME MATCHES "Windows")
	set(VCPKG_TARGET_TRIPLET "x64-windows" CACHE STRING "Vcpkg target triplet")
elseif (CMAKE_SYSTEM_NAME MATCHES "Linux")
	# vcpkg dynamic library for linux is shit.
	# set(VCPKG_TARGET_TRIPLET "x64-linux-dynamic" CACHE STRING "Vcpkg target triplet")
	# set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib" CACHE STRING "Dynamic library find path")
	# set(VCPKG_FIXUP_ELF_RPATH TRUE CACHE BOOL "Vcpkg runpath ")
	set(VCPKG_TARGET_TRIPLET "x64-linux" CACHE STRING "Vcpkg target triplet")
endif()

project ("03_vcpkg")

set(CMAKE_CXX_STANDARD 17 CACHE STRING "The C++ standard to use")
set(CMAKE_CXX_STANDARD_REQUIRED True CACHE BOOL "Whether the C++ standard is required")
set(CMAKE_CXX_EXTENSIONS False CACHE BOOL "Whether to use compiler-specific C++ extensions")

# 只有构建工具是makefile或者Ninja才生效。
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE BOOL "Whether to export compile commands for the project")

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
	# 默认
	# set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")
endif()

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
    RUNTIME DESTINATION bin
)
