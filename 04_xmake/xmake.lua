add_rules("mode.debug", "mode.release")

if is_plat("windows") then
  set_runtimes("MD")
  set_toolchains("msvc")
  set_languages("c++17")
  add_cxxflags("cl::/utf-8")
end

set_installdir("$(buildir)/install/$(arch)-$(mode)")

add_requires("glfw 3.4", {configs = {shared = true}})
add_requires("spdlog 1.14.1")
add_requires("assimp 5.4.3", {configs = {shared = true}})

includes("3rd/*/xmake.lua")

target("04_xmake")
    set_kind("binary")
    add_packages("glfw","spdlog")
    add_deps("glad","glm", "stb_image")
    add_files("src/*.cpp")
    add_includedirs("src")
    add_installfiles("(resources/images/*)", {prefixdir = "bin"})
    add_installfiles("(resources/shaders/*)", {prefixdir = "bin"})
    after_build(function (target)
      print("before_build")
      print("copying resource " .." to " .. target:targetdir())
      os.cp(path.join("$(scriptdir)", "Resources"), target:targetdir())
    end)