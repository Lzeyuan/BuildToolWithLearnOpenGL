cmake_minimum_required(VERSION 3.25)

project(06_LightCasters VERSION 1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(MODEL "07_Model")
add_executable(
    ${MODEL}
    main.cpp
    model.h
    mesh.h
)

target_precompile_headers(
    ${MODEL}
    REUSE_FROM
    Base
)

 find_package(assimp CONFIG REQUIRED)

target_link_libraries(
    ${MODEL}
    PRIVATE
    Base
    assimp::assimp
)

# 复制资源
set(RESOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Resources)
if (EXISTS "${RESOURCE_DIR}")
  add_custom_command(
      TARGET ${MODEL}
      PRE_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy_directory ${RESOURCE_DIR} "$<TARGET_FILE_DIR:${MODEL}>/Resources"
      COMMENT "复制Resource文件夹到 $<TARGET_FILE_DIR:${MODEL}>/Resources"
  )
endif ()