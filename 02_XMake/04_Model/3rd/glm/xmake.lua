add_rules("mode.release", "mode.debug")

-- 2.5.9 之前写法
-- target("glm")
--   set_kind("static")
--   add_includedirs("include", { public = true })

target("glm")
  set_kind("headeronly")
  add_includedirs("include", { public = true })