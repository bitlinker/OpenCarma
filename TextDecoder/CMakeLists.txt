cmake_minimum_required(VERSION 2.6)
project(TextDecoder)

set(TEXTDECODER_SOURCES
        ../Common/TextDecoder.h
        ../Common/TextDecoder.cpp
        main.cpp
        )

set(TEXTDECODER_INCLUDE_DIRS
        ../Common
        )

INCLUDE_DIRECTORIES(${TEXTDECODER_INCLUDE_DIRS})

# Link
add_executable(TextDecoder ${TEXTDECODER_SOURCES})
target_link_libraries(TextDecoder BitlinkerCommons)