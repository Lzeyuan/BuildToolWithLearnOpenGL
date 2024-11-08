# LearnCMakeWithOpenGL
通过搭建[LearnOpenGL](https://learnopengl-cn.github.io/)环境，学习C/C++Build。

# CMake
## 缓存
- set(... CACHE)
- option
- find_package、find_program、find_library、find_file

## 功能版本限制
- `include(FetchContent)`：CMake 3.11
- `CMAKE_MSVC_RUNTIME_LIBRARY`：CMake 3.15

# 动态库
Window默认会从程序当前目录开始查找，Linux从RPATH开始。

## linux使用动态库开发有点麻烦：
**问题场景**：我想 `cmake --install` 测试实际运行情况。Windows因为从程序当前目录开始查找，所以测试很方便。

**但是Linux就不好说了**：

要为Vcpkg管理的每个包设置 `-Wl,-rpath,/path/to/your/library`

幸运的是可以开启 `X_VCPKG_APPLOCAL_DEPS_INSTALL`自动设置

但是运行`cmake --install`安装会把设置好的程序`RPATH` **清空！！**。

**解决方法**

和windows一样的把所有so复制到bin目录

临时设置`export LD_LIBRARY_PATH=/path/to/your/library:$LD_LIBRARY_PATH`，运行即可。