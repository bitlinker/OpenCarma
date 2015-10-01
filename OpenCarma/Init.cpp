#include <Render/RenderCommon.h>
#include <Init.h>
#include <Exception/Exception.h>

namespace OpenCarma
{
    Init::Init()
    {
        if (GL_TRUE != glfwInit()) // TODO: init in window class? GLFW singleton initializer?
            throw Commons::UnknownException("Can't init GLFW");       
    }


    Init::~Init()
    {
        glfwTerminate();
    }
}