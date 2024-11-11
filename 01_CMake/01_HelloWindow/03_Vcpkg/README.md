# Vpkg
## 推荐使用清单模式
**所有配置都要写在project之前**

**X开头的配置都是实验性的**

下面配置基本和平台相关最好写在 `CMakeUserPreset.json` 里

> 注意！`CMakePreset.json`和`CMakeLists.txt`不一致，要小写`$env`，详见文档[文档](https://cmake.org/cmake/help/latest/manual/cmake-presets.7.html#macro-expansion)。
```cmake
# VCPKG_ROOT 为 vcpkg根目录，写在环境变量里
set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "The C++ standard to use")
```

```cmake
# 选择架构
# windwos默认动态库,x64-windows-statics
# linux静态库，x64-linux-dynamic
set(VCPKG_TARGET_TRIPLET "x64-windows" CACHE STRING "Vcpkg target triplet")
set(VCPKG_TARGET_TRIPLET "x64-linux" CACHE STRING "Vcpkg target triplet")

# Only linux can do
# 设置动态库搜索路径
set(VCPKG_FIXUP_ELF_RPATH TRUE CACHE BOOL "Vcpkg runpath ")
# 设置安装时程序rpath
set(CMAKE_INSTALL_RPATH "youpath/out/build/linux-x64-release/vcpkg_installed/x64-linux-dynamic/lib" CACHE STRING "Dynamic library find path")

# Only windows can do，配置dll复制
set(X_VCPKG_APPLOCAL_DEPS_INSTALL TRUE CACHE BOOL "Vcpkg runpath ")

```
> vcpkg不认为linux下install后还需要设置rpath。[Make Linux dynamic linkage a first class citizen](https://github.com/microsoft/vcpkg/discussions/19127)