add_rules("mode.debug", "mode.release")

if is_plat("windows") then
  set_runtimes("MD")
  set_toolchains("msvc")
  add_cxxflags("cl::/utf-8")
  add_requires("glfw 3.4", {configs = {shared = true}})
  add_requires("assimp 5.4.3", {configs = {shared = true}})
else 
  add_requires("glfw 3.4")
  add_requires("assimp 5.4.3")
end 

set_languages("c++17")
set_installdir("$(buildir)/install/$(arch)-$(mode)")

includes("3rd/*/xmake.lua")

target("02_Introduction")
    set_kind("binary")
    add_packages("glfw", "assimp")
    set_pcxxheader("src/stdafx.hpp")
    add_deps("glad","glm", "stb_image")
    add_files("src/*.cpp")
    add_includedirs("src")
    add_installfiles("(resources/textures/*)", {prefixdir = "bin"})
    add_installfiles("(resources/shaders/*)", {prefixdir = "bin"})
    after_build(function (target)
      print("before_build")
      print("copying resource " .." to " .. target:targetdir())
      os.cp(path.join("$(scriptdir)", "resources"), target:targetdir())
    end)