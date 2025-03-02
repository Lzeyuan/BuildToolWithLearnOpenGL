# ！！！！此目录仅记录旧项目！！！！

# 介绍
以[LearnOpenGL](https://learnopengl-cn.github.io)项目为例子，学习CMake

# 环境
- Winodwos11
- ~~VS2022~~（智能提示有bug） 
- clion nova
- CMake > 3.25：为了支持c++20模块
- 第三方库：
[GLFW](https://www.glfw.org/download.html)、
[GLAD](https://glad.dav1d.de/)

# 快速开始
`git clone --recursive https://github.com/Lzeyuan/****.git`

# 项目结构
- 3rd：存放第三方库
- 数字_项目名：LearnOpenGL阶段性项目

# CMake笔记
## 配置CMakePresets.json和CMakeUserPresets.json
`CMakePresets.json`：总配置<br>
`CMakeUserPresets.json`：用户根据本地环境自定义配置，因此不应该上传到仓库<br><br>

下面建议使用vscode配合插件验证查看，因为输出比较全面<br>
`configurePresets`：用于CMake生成项目阶段添加参数，下面是本项CMake配置Debug模式参数等价powershell指令
```powershell
$commandsArray = @(
    # CMake install
    'cmake.exe',
    # 添加VS项目Debug配置
    '"-DCMAKE_CONFIGURATION_TYPES=Debug;"',
    '-DCMAKE_BUILD_TYPE=Debug',
    # MSVC编译器
    '-DCMAKE_C_COMPILER=cl.exe',
    '-DCMAKE_CXX_COMPILER=cl.exe',
    # CMake install、源文件目录、生成目录
    '-DCMAKE_INSTALL_PREFIX=D:/Development/Project/Cpp/CMakeLearn/out/install/cpp20',
    '-SD:/Development/Project/Cpp/CMakeLearn',
    '-BD:/Development/Project/Cpp/CMakeLearn/out/build/cpp20',
    # 生成VS项目指令
    '-G "Visual Studio 17 2022" -A x64'
)

# 将命令集合在一起
$fullCommand = $commandsArray -join ' '

# 执行命令
Invoke-Expression $fullCommand

```

`cacheVariables`：CMake时加-D <br>

因为C++通病，生成器、编译器参数各不相同，下面是生成CMake配置Ninja和VS对比<br>
**生成器是VS时**
```json
"generator": "Visual Studio 17 2022",
"architecture": {
    "strategy": "set",
    "value": "x64"
},
```
**生成器是Ninja时**
```json
"generator": "Ninja",
"architecture": {
    "strategy": "external",
    "value": "x64"
},
```

`buildPresets`：用于CMake编译阶段添加参数，下面是编译时VS所需参数<br>
**生成器是VS时**
```json
"buildPresets": [
    {
        "name": "debug-build",
        "displayName": "Debug",
        "configurePreset": "cpp20-debug",
        "configuration": "Debug",
        "verbose": true
    }
]
```
`configurePreset`关联上面`configurePresets`<br>
`CMAKE_CONFIGURATION_TYPES`和`configurePreset`对应，编译时添加MSBuild参数`--config Debug`<br>
`verbose`用于详细输出编译过程<br>

**生成器是Ninja时**
不需要配置