cmake_minimum_required (VERSION 3.8)

project ("02_FetchContent")
if (MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /utf-8")
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")
    # set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()
if (UNIX)
	set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE BOOL "Whether to export compile commands for the project")
endif()
set(CMAKE_CXX_STANDARD 17 CACHE STRING "The C++ standard to use")
set(CMAKE_CXX_STANDARD_REQUIRED True CACHE BOOL "Whether the C++ standard is required")
set(CMAKE_CXX_EXTENSIONS False CACHE BOOL "Whether to use compiler-specific C++ extensions")

add_executable (
    ${PROJECT_NAME} 
    src/main.cpp
)

add_subdirectory(3rd/glad)

# FetchContent必须大写
include(FetchContent)
set(FETCHCONTENT_QUIET OFF)
set(FETCHCONTENT_BASE_DIR ${PROJECT_SOURCE_DIR}/fetch_content)

fetchcontent_declare(
    glfw													# 库名字
    GIT_REPOSITORY https://github.com/glfw/glfw.git			# 仓库地址
    GIT_TAG 3.4												# 库版本
)

fetchcontent_declare(
    spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG v1.14.1
)

option(BUILD_SHARED_LIBS "Build shared libraries" ON)
option(GLFW_BUILD_EXAMPLES "Build the GLFW example programs" OFF)
option(GLFW_BUILD_TESTS "Build the GLFW test programs" OFF)
option(GLFW_BUILD_DOCS "Build the GLFW documentation" OFF)
option(GLFW_INSTALL "Generate installation target" ON)
option(SPDLOG_INSTALL "Generate the install target" ON)
option(SPDLOG_BUILD_SHARED "Build shared library" ON)
FetchContent_MakeAvailable(glfw spdlog)

target_include_directories(
    ${PROJECT_NAME} 
    PRIVATE
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