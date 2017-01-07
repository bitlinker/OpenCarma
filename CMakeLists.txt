cmake_minimum_required (VERSION 2.6)
project (OpenCarma)

# Sources
set(BITLINKER_COMMONS_SOURCES
    BitlinkerCommons/Common/EndianUtils.cpp
    
    #Logger
    BitlinkerCommons/Logger/Log.h
    BitlinkerCommons/Logger/Log.cpp
    
    #Render
    BitlinkerCommons/Render/BufferObject.h
    BitlinkerCommons/Render/Camera.h
    BitlinkerCommons/Render/Camera.cpp
    BitlinkerCommons/Render/IBindable.h    
    BitlinkerCommons/Render/RenderCommon.h
    BitlinkerCommons/Render/GLContext.h
    BitlinkerCommons/Render/GLContext.cpp
    BitlinkerCommons/Render/ScopeBind.h
    BitlinkerCommons/Render/Shader.h
    BitlinkerCommons/Render/Shader.cpp
    BitlinkerCommons/Render/ShaderProgram.h
    BitlinkerCommons/Render/ShaderProgram.cpp
    BitlinkerCommons/Render/Texture.h
    BitlinkerCommons/Render/Texture.cpp
    BitlinkerCommons/Render/VertexArrayObject.h
    BitlinkerCommons/Render/RenderWindow.h
    BitlinkerCommons/Render/RenderWindow.cpp
    BitlinkerCommons/Render/RenderNode.h
    BitlinkerCommons/Render/RenderNode.cpp
    
    #Streams
    BitlinkerCommons/Streams/FileStream.h
    BitlinkerCommons/Streams/FileStream.cpp
)

set(COMMON_SOURCES
    Common/TextDecoder.cpp
)

set(OPENCARMA_SOURCES
    OpenCarma/Render/AxisDrawable.cpp
    OpenCarma/Render/CarmaTextureLoader.cpp
    OpenCarma/Render/FreeFlyCameraController.cpp
    OpenCarma/Render/Render.cpp
    OpenCarma/Render/RenderMaterial.cpp
    OpenCarma/Render/StaticModel.cpp
    OpenCarma/Render/TextureManager.cpp
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
    BRenderLib/BigEndianStreamReader.cpp
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
ADD_DEFINITIONS(/D _CRT_SECURE_NO_WARNINGS)


# External libs:
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake/Modules/")

FIND_PACKAGE (GLFW3 REQUIRED)
FIND_PACKAGE (GLEW REQUIRED)
FIND_PACKAGE (GLM REQUIRED)

INCLUDE_DIRECTORIES (${GLFW3_INCLUDE_DIR} ${GLEW_INCLUDE_DIR} ${GLM_INCLUDE_DIR})

# Link
add_executable(OpenCarma ${COMMON_SOURCES} ${BITLINKER_COMMONS_SOURCES} ${OPENCARMA_SOURCES} ${BRENDER_SOURCES})
target_link_libraries(OpenCarma opengl32.lib ${GLFW3_LIBRARY} ${GLEW_LIBRARY})

add_subdirectory("TextDecoder")

#install(TARGETS opencarma DESTINATION /usr/lib) #TODO