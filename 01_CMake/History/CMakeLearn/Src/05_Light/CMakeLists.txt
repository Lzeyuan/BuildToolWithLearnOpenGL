cmake_minimum_required(VERSION 3.25)

project(05_Light VERSION 1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(
    ${PROJECT_NAME}
    main.cpp
)

target_precompile_headers(
    ${PROJECT_NAME}
    REUSE_FROM
    Base
)

target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE
    Base
)

# 复制资源
set(RESOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Resources)
if (EXISTS "${RESOURCE_DIR}")
  add_custom_command(
      TARGET ${PROJECT_NAME}
      PRE_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy_directory ${RESOURCE_DIR} "$<TARGET_FILE_DIR:${PROJECT_NAME}>/Resources"
      COMMENT "复制Resource文件夹到 $<TARGET_FILE_DIR:${PROJECT_NAME}>/Resources"
  )
endif ()

