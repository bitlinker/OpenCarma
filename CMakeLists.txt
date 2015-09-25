cmake_minimum_required (VERSION 2.6)
project (OpenCarma)

# Sources
set(COMMON_SOURCES
    Common/TextDecoder.cpp
)

set(OPENCARMA_SOURCES
    OpenCarma/AxisDrawable.cpp
    OpenCarma/Camera.cpp
    OpenCarma/CarmaTextureLoader.cpp
    OpenCarma/FreeFlyCameraController.cpp
    OpenCarma/Init.cpp
    OpenCarma/Log.cpp
    OpenCarma/main.cpp
    OpenCarma/OpponentDescription.cpp
    OpenCarma/RaceDescription.cpp
    OpenCarma/Render.cpp
    OpenCarma/RenderMaterial.cpp
    OpenCarma/RenderNode.cpp
    OpenCarma/Scene.cpp
    OpenCarma/Shader.cpp
    OpenCarma/ShaderProgram.cpp
    OpenCarma/StaticModel.cpp
    OpenCarma/TextReader.cpp
    OpenCarma/Texture.cpp
    OpenCarma/TextureManager.cpp
	
	OpenCarma/TextFiles/SoundTxt.cpp
	OpenCarma/TextFiles/PedestrnTxt.cpp	
	
	OpenCarma/Sound/SoundMgr.cpp
)

set(BRENDER_SOURCES
    BRenderLib/BigEndianStreamReader.cpp
    BRenderLib/EndianConverter.cpp
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
    BRenderLib
    BRenderLib/Serialization
    BRenderLib/Objects
)
INCLUDE_DIRECTORIES(${INCLUDE_DIRS})

SOURCE_GROUP("Common" FILES ${COMMON_SOURCES})
SOURCE_GROUP("OpenCarma" FILES ${OPENCARMA_SOURCES})
SOURCE_GROUP("BRender" FILES ${BRENDER_SOURCES})


# Platform-specific configs:
ADD_DEFINITIONS(/D _CRT_SECURE_NO_WARNINGS)


# External libs:
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake/Modules/")

FIND_PACKAGE (GLFW3 REQUIRED)
FIND_PACKAGE (GLEW REQUIRED)
FIND_PACKAGE (GLM REQUIRED)

INCLUDE_DIRECTORIES (${GLFW3_INCLUDE_DIR} ${GLEW_INCLUDE_DIR} ${GLM_INCLUDE_DIR})

# Link
add_executable(OpenCarma ${COMMON_SOURCES} ${OPENCARMA_SOURCES} ${BRENDER_SOURCES})
target_link_libraries(OpenCarma opengl32.lib ${GLFW3_LIBRARY} ${GLEW_LIBRARY})

add_subdirectory("TextDecoder")

#install(TARGETS opencarma DESTINATION /usr/lib) #TODO