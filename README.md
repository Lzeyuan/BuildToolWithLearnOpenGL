# LearnCMakeWithOpenGL
通过搭建[LearnOpenGL](https://learnopengl-cn.github.io/)环境，学习C/C++Build。

# 推荐使用xmake!


# CMake
## 模板
```cmake
# 必须
cmake_minimum_required (VERSION 3.19)

# 必须在peroject前才生效，最好写在CMakeUserPreset.json
# set(VCPKG_TARGET_TRIPLET "x64-linux" CACHE STRING "Vcpkg target triplet")
# set(VCPKG_TARGET_TRIPLET "x64-windows" CACHE STRING "Vcpkg target triplet")
# set(VCPKG_FIXUP_ELF_RPATH TRUE CACHE BOOL "Vcpkg runpath ")
# set(X_VCPKG_APPLOCAL_DEPS_INSTALL TRUE CACHE BOOL "Vcpkg runpath ")

# 必须，这个前后set某些变量有顺序要求
project ("03_vcpkg")

# 判断平台，project后生效
if (CMAKE_SYSTEM_NAME MATCHES "Windows")
elseif (CMAKE_SYSTEM_NAME MATCHES "Linux")
endif()

# C++版本
set(CMAKE_CXX_STANDARD 17 CACHE STRING "The C++ standard to use")
set(CMAKE_CXX_STANDARD_REQUIRED True CACHE BOOL "Whether the C++ standard is required")
set(CMAKE_CXX_EXTENSIONS False CACHE BOOL "Whether to use compiler-specific C++ extensions")

# 只有构建工具是makefile或者Ninja才生效。
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE BOOL "Whether to export compile commands for the project")

# 判断编译器clang,gcc,msvc
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
	# 默认
	# set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")
endif()

# 查找包
find_package(glfw3 CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)

# 子项目
add_subdirectory(3rd/glad)

# 生成目标，add_library，add_executable
add_executable (
	${PROJECT_NAME}
	src/main.cpp
  )

# 链接
target_link_libraries(
	${PROJECT_NAME}
	PRIVATE
	glad
	glfw
	spdlog::spdlog
)

# 安装
install(
    TARGETS ${PROJECT_NAME}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

```
## 缓存
- set(... CACHE ...)
- option
- find_package、find_program、find_library、find_file

## 功能版本限制
- `include(FetchContent)`：CMake 3.11
- `CMAKE_MSVC_RUNTIME_LIBRARY`：CMake 3.15
- `CMakePreset.json`：CMake 3.19

# 动态库
Window默认会从程序当前目录开始查找，Linux从RPATH开始。

## linux使用动态库开发有点麻烦：
**问题场景**：我想 `cmake --install` 测试实际运行情况。Windows因为从程序当前目录开始查找，所以测试很方便。

### Windows方便点

开启 `X_VCPKG_APPLOCAL_DEPS_INSTALL` dll和exe一起安装。

### 但是Linux就不好说了

要为Vcpkg管理的每个包设置 `-Wl,-rpath,/path/to/your/library`

幸运的是可以开启 `VCPKG_FIXUP_ELF_RPATH`自动设置
```cmake
# vcpkg dynamic library for linux is shit.
# 自动设置
set(VCPKG_TARGET_TRIPLET "x64-linux-dynamic" CACHE STRING "Vcpkg target triplet")
set(VCPKG_FIXUP_ELF_RPATH TRUE CACHE BOOL "Vcpkg runpath ")

# 手动设置
# set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib" CACHE STRING "Dynamic library find path")
```

但是运行`cmake --install`安装会把设置好的程序`RPATH` **清空！！**。

### 解决方法

不能和windows一样使用 `X_VCPKG_APPLOCAL_DEPS_INSTALL` 自动复制动态库。

所以要手动把所有so复制到 `/path/to/your/library` 目录。

然后执行指令：`LD_LIBRARY_PATH=/path/to/your/library ./YouAPP`。