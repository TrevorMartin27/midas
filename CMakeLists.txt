cmake_minimum_required(VERSION 3.11)
project(Midas
	VERSION 1.0
	LANGUAGES CXX
)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(FILES ${FILES}
	src/image.cpp
	src/palette.cpp
	src/dither.cpp
	src/main.cpp
)

add_executable(midas ${FILES})
target_include_directories(midas PRIVATE include/)