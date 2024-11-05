# 包管理 2
## 1 install and find_package
### 1.1 使用
```cmake
# 参考https://cmake.org/cmake/help/latest/command/find_package.html#config-mode-search-procedure
# 设置查找目录
set(CMAKE_PREFIX_PATH E:\\projects\\LearnCMakeWithOpenGL\\03_install\\mock_install\\x64-Debug\\lib\\cmake)

find_package(glfw3 CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
```

### 1.2 生成
```cmake
# 设置安装目录
set(CMAKE_INSTALL_PREFIX E:\\projects\\LearnCMakeWithOpenGL\\03_install\\mock_install)

# 例子
install(
    TARGETS glad
    EXPORT glad                                     # 导出名字
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
```

因为`cmake install`认为是把库安装到环境变量里，这里只是测试，所以要手动把动态库复制到执行文件同一目录。

