cmake_minimum_required(VERSION 3.4.3)

set(PROJECT_NAME propagator)

project(${PROJECT_NAME})

set(SOURCE_FILES
	src/main.cpp
)

set(SERIAL_LIB_FILES
	../serialib/lib/serialib.h
	../serialib/lib/serialib.cpp)

add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${SERIAL_LIB_FILES})