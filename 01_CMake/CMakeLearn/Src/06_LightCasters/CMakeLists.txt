cmake_minimum_required(VERSION 3.25)

project(06_LightCasters VERSION 1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(LIGHT_CASTERS "06_1_LightCasters")
add_executable(
    ${LIGHT_CASTERS}
    main.cpp
)

target_precompile_headers(
    ${LIGHT_CASTERS}
    REUSE_FROM
    Base
)

target_link_libraries(
    ${LIGHT_CASTERS}
    PRIVATE
    Base
)

# 复制资源
set(RESOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Resources)
if (EXISTS "${RESOURCE_DIR}")
  add_custom_command(
      TARGET ${LIGHT_CASTERS}
      PRE_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy_directory ${RESOURCE_DIR} "$<TARGET_FILE_DIR:${LIGHT_CASTERS}>/Resources"
      COMMENT "复制Resource文件夹到 $<TARGET_FILE_DIR:${LIGHT_CASTERS}>/Resources"
  )
endif ()

set(MULTIPLE_LIGHT "06_2_MultipleLights")
add_executable(
    ${MULTIPLE_LIGHT}
    multiple_lights.cpp
)

target_precompile_headers(
    ${MULTIPLE_LIGHT}
    REUSE_FROM
    Base
)

target_link_libraries(
    ${MULTIPLE_LIGHT}
    PRIVATE
    Base
)