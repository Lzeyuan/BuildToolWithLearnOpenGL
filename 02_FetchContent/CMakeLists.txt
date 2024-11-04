cmake_minimum_required (VERSION 3.8)

project ("02_FetchContent")
# 设置 C++ 编译器选项以启用 UTF-8 编码
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /utf-8")

add_executable (
    ${PROJECT_NAME} 
    src/main.cpp
)

add_subdirectory(3rd/glad)

include(fetchcontent)
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
    opengl32
    spdlog::spdlog
)

install(
    TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
)