# Vpkg
## 推荐使用清单模式
使用vcpkg，`$ENV{VCPKG_ROOT}`是环境变量也可以替换为实际路径。

> 注意！`CMakePreset.json`和`CMakeLists.txt`不一致，要小写`$env`，详见文档[文档](https://cmake.org/cmake/help/latest/manual/cmake-presets.7.html#macro-expansion)。
```cmake
set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "The C++ standard to use")
```

选择架构写在`CMakelists.txt`比较方便
```cmake
set(VCPKG_TARGET_TRIPLET "x64-windows" CACHE STRING "Vcpkg target triplet")
set(VCPKG_TARGET_TRIPLET "x64-linux" CACHE STRING "Vcpkg target triplet")
```

