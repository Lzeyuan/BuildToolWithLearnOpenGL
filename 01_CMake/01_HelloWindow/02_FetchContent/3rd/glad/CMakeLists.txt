cmake_minimum_required (VERSION 3.8)

add_library (
	glad
	STATIC
	src/glad.c
)

target_include_directories(
	glad
	PUBLIC
	include
)

install(
    TARGETS glad
    EXPORT glad
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})