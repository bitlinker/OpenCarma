#include <RenderCommon.h>
#include <Init.h>
#include <Exception.h>

namespace OpenCarma
{
    Init::Init()
    {
        if (GL_TRUE != glfwInit())
            throw UnknownException("Can't init GLFW");       
    }


    Init::~Init()
    {
        glfwTerminate();
    }
}