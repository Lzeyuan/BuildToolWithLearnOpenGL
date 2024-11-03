# 你好窗口
## 1 配置化管理第三方库 —— fetchcontent
### 1.1 使用理由
C++使用第三方库有几个方法：
1. git克隆下来编译
2. 包管理帮你克隆下来编译
3. 编译好静态库或动态库文件直接使用

项目管理最大问题之一就是版本管理，方法1对于版本管理要手动操作，方法2可以自动化配置，方法3多人合作中很容易出问题。

**个人观点**：cmake源码版本 > 包管理（conan、vcpkg）> git submodule

### 1.2 fetchcontent例子
```cmake
...
# 类似 #include
include(fetchcontent)
# 下载显示过程
set(FETCHCONTENT_QUIET OFF)
# 设置下载源码目录
set(FETCHCONTENT_BASE_DIR ${PROJECT_SOURCE_DIR}/fetch_content)
# 定义下载库
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

# glfw配置
option(BUILD_SHARED_LIBS "Build shared libraries" ON)
option(GLFW_BUILD_EXAMPLES "Build the GLFW example programs" OFF)
option(GLFW_BUILD_TESTS "Build the GLFW test programs" OFF)
option(GLFW_BUILD_DOCS "Build the GLFW documentation" OFF)
option(GLFW_INSTALL "Generate installation target" OFF)
# spdlg配置
option(SPDLOG_INSTALL "Generate the install target" OFF)
option(SPDLOG_BUILD_SHARED "Build shared library" ON)

# 实际下载 + add_subdirectory
FetchContent_MakeAvailable(glfw)
...
```

在 `main.cpp` 里添加 `#include "spdlog/spdlog.h"`，这里把库都设置成了**动态库**，在main里随便使用一下spdlog的功能：`spdlog::info("Welcome to spdlog!");`。

## 2 install
本质就是把一些东西复制到一个地方里。

那有什么用呢？
- 安装到系统里
- 这里为了换个环境测试使用情况

```cmake
...

install(
    TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
)
```

重新配置CMake后可以在gui看到多了一个（安装）的编译目标。

这时使用这个选项编译，运行，会提示缺少 **glfw.dll** 和 **spdlog.dll**

回过头可以见到上面的配置，找到并修改为下面两个选项：
- option(SPDLOG_BUILD_SHARED "Build shared library" ON)
- option(GLFW_INSTALL "Generate installation target" ON)

重新重新配置CMake编译器，运行，此时就可以正常运行了。

一些库没有写install，就只能自己去修改了，这里复制spdlog的处理：
```cmake
install(DIRECTORY include/ DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}" PATTERN "fmt/bundled" EXCLUDE)
install(
    TARGETS spdlog spdlog_header_only
    EXPORT spdlog
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
```

没有`uninstall`配置。