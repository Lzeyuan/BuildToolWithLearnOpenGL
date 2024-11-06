add_rules("mode.release", "mode.debug")

target("glm")
  set_kind("static")
  add_includedirs("include", { public = true })
