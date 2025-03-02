cmake_minimum_required (VERSION 3.25)

if(VCPKG_TOOLCHAIN_FILE)
    string(REPLACE "\\" "/" converted_path "${VCPKG_TOOLCHAIN_FILE}")
	list(APPEND CMAKE_TOOLCHAIN_FILE ${converted_path})
else()
    message(FATAL_ERROR "please set vcpkg tool file")
endif()

project ("CMakeLearn")

# 包含子项目。
add_subdirectory ("ThirdPart")
add_subdirectory ("Base")
add_subdirectory(Src)
