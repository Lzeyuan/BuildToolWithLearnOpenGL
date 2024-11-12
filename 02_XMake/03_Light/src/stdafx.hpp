#ifndef STDAFX_HPP_
#define STDAFX_HPP_
// IWYU pragma: begin_exports
#include <cstdio>
#include <fstream>
#include <functional>
#include <iostream>
#include <memory>
#include <optional>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>


// glad must be before GLFW
// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// clang-format on
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stb_image.h>
// IWYU pragma: end_exports
#endif //  STDAFX_HPP_