# Vpkg
## 推荐使用清单模式
**所有配置都要写在project之前**

使用vcpkg，`$ENV{VCPKG_ROOT}`是环境变量也可以替换为实际路径。

> 注意！`CMakePreset.json`和`CMakeLists.txt`不一致，要小写`$env`，详见文档[文档](https://cmake.org/cmake/help/latest/manual/cmake-presets.7.html#macro-expansion)。
```cmake
set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "The C++ standard to use")
```

```cmake
# 选择架构
# windwos默认动态库,x64-windows-statics
# linux静态库，x64-linux-dynamic
set(VCPKG_TARGET_TRIPLET "x64-windows" CACHE STRING "Vcpkg target triplet")
set(VCPKG_TARGET_TRIPLET "x64-linux" CACHE STRING "Vcpkg target triplet")

# Only linux can do，设置动态库搜索路径
set(VCPKG_FIXUP_ELF_RPATH TRUE CACHE BOOL "Vcpkg runpath ")
# Only windows can do，配置dll复制
set(X_VCPKG_APPLOCAL_DEPS_INSTALL TRUE CACHE BOOL "Vcpkg runpath ")
```

