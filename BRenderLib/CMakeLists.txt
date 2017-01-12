cmake_minimum_required(VERSION 2.6)
project(BRenderLib)

set(BRENDER_SOURCES
        EndianStreamReader.cpp
        Serialization/ActorSerializer.cpp
        Serialization/MaterialSerializer.cpp
        Serialization/ModelSerializer.cpp
        Serialization/TextureSerializer.cpp
        Objects/Actor.cpp
        Objects/ChunkHeader.cpp
        Objects/Material.cpp
        Objects/Model.cpp
        Objects/Pixmap.cpp
        )

# TODO: include commons when needed
#set(INCLUDE_DIRS
#        Serialization
#        Objects
#        )
#
#INCLUDE_DIRECTORIES(${INCLUDE_DIRS})

add_library(BRenderLib ${BRENDER_SOURCES})