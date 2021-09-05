cmake_minimum_required(VERSION 3.4.3)

set(PROJECT_NAME propagator)

project(${PROJECT_NAME})

add_definitions(-DGL_SILENCE_DEPRECATION=1)

add_subdirectory(../glfw ${CMAKE_BINARY_DIR}/glfw)

# Serialib -----

set(SERIAL_LIB_FILES
	../serialib/lib/serialib.h
	../serialib/lib/serialib.cpp)

add_library(
	serialib STATIC
    ${SERIAL_LIB_FILES}
)

# NanoVG -----

set(NANOVG_FILES
	../nanovg/src/fontstash.h
	../nanovg/src/nanovg.c
	../nanovg/src/nanovg.h
	../nanovg/src/nanovg_gl.h
	../nanovg/src/nanovg_gl_utils.h
	../nanovg/src/stb_image.h
	../nanovg/src/stb_truetype.h)

add_library(
    nanovg STATIC
    ${NANOVG_FILES}
)

find_package(OpenGL REQUIRED)

target_include_directories(nanovg PUBLIC ${OPENGL_INCLUDE_DIR})
target_link_libraries(nanovg ${OPENGL_gl_LIBRARY})

# Propagator -----

set(SOURCE_FILES
	src/main.cpp
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC
						   ../serialib/lib
						   ../nanovg/src
						   ../glfw/include)

target_link_libraries(${PROJECT_NAME} PUBLIC glfw nanovg serialib)