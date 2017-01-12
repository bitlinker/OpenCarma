cmake_minimum_required (VERSION 2.6)
project (BRenderTest)

set(TEST_SOURCES
    ../Common/TextDecoder.cpp
	main.cpp
)

set(TEST_INCLUDE_DIRS
    ../Common
)

INCLUDE_DIRECTORIES(${TEST_INCLUDE_DIRS})

# Link
add_executable(BRenderTest ${TEST_SOURCES})