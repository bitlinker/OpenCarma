cmake_minimum_required(VERSION 2.6)
project (OpenCarma)

set(COMMON_SOURCES
    Common/TextDecoder.cpp
)

set(OPENCARMA_SOURCES
    OpenCarma/Render/AxisDrawable.cpp
    OpenCarma/Render/CarmaTextureLoader.cpp
    OpenCarma/Render/FreeFlyCameraController.cpp
    OpenCarma/Render/RenderMaterial.cpp
    OpenCarma/Render/StaticModel.cpp
    OpenCarma/Render/PlainShaderProgram.h
    OpenCarma/Render/PlainShaderProgram.cpp
    
    OpenCarma/main.cpp
    OpenCarma/OpponentDescription.cpp
    OpenCarma/RaceDescription.cpp

    OpenCarma/TextFiles/TextReader.cpp
	OpenCarma/TextFiles/SoundTxt.cpp
	OpenCarma/TextFiles/PedestrnTxt.cpp    
    OpenCarma/TextFiles/RaceTxt.cpp
    OpenCarma/TextFiles/RaceTxt.h
	
	OpenCarma/Sound/SoundMgr.cpp
)

set(BRENDER_SOURCES
        BRenderLib/EndianStreamReader.cpp
    BRenderLib/Serialization/ActorSerializer.cpp
    BRenderLib/Serialization/MaterialSerializer.cpp
    BRenderLib/Serialization/ModelSerializer.cpp
    BRenderLib/Serialization/TextureSerializer.cpp
    BRenderLib/Objects/Actor.cpp
    BRenderLib/Objects/ChunkHeader.cpp
    BRenderLib/Objects/Material.cpp
    BRenderLib/Objects/Model.cpp
    BRenderLib/Objects/Pixmap.cpp
)


# Includes
set(INCLUDE_DIRS
    Common
	BitlinkerCommons
    OpenCarma
	OpenCarma/TextFiles
    OpenCarma/Render
    BRenderLib
    BRenderLib/Serialization
    BRenderLib/Objects
)
INCLUDE_DIRECTORIES(${INCLUDE_DIRS})

SOURCE_GROUP("BitlinkerCommons" FILES ${BITLINKER_COMMONS_SOURCES})
SOURCE_GROUP("Common" FILES ${COMMON_SOURCES})
SOURCE_GROUP("OpenCarma" FILES ${OPENCARMA_SOURCES})
SOURCE_GROUP("BRender" FILES ${BRENDER_SOURCES})

# Platform-specific configs:
# Windows
#ADD_DEFINITIONS(/D _CRT_SECURE_NO_WARNINGS)

#MinGW
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -stdlib=libc++ -std=c99 -DGLEW_STATIC")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11 -std=gnu++11 -DGLEW_STATIC")

# External libs:
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake/Modules/")

FIND_PACKAGE (GLFW3 REQUIRED)
FIND_PACKAGE (GLEW REQUIRED)
FIND_PACKAGE (GLM REQUIRED)

INCLUDE_DIRECTORIES (${GLFW3_INCLUDE_DIR} ${GLEW_INCLUDE_DIR} ${GLM_INCLUDE_DIR})

add_subdirectory("BitlinkerCommons")
add_subdirectory("BRenderLib")
add_subdirectory("TextDecoder")

#add_subdirectory("BRenderTest")

# Link
add_executable(OpenCarma ${COMMON_SOURCES} ${BITLINKER_COMMONS_SOURCES} ${OPENCARMA_SOURCES} ${BRENDER_SOURCES})
target_link_libraries(OpenCarma ${GLFW3_LIBRARY} ${GLEW_LIBRARY} opengl32.lib)

#install(TARGETS opencarma DESTINATION /usr/lib) #TODO