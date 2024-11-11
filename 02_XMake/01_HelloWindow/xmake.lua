add_rules("mode.debug", "mode.release")

if is_plat("windows") then
  set_runtimes("MD")
  set_toolchains("msvc")
  add_requires("glfw 3.4", {configs = {shared = true}})
else 
  add_requires("glfw 3.4")
end

add_cxxflags("cl::/utf-8")

set_languages("c++17")
set_installdir("$(buildir)/install/$(arch)-$(mode)")

includes("3rd/*/xmake.lua")

target("01_HelloWindow")
  set_kind("binary")
  set_pcxxheader("src/stdafx.hpp")
  add_packages("glfw")
  add_deps("glad")
  add_files("src/*.cpp")
  add_includedirs("src")