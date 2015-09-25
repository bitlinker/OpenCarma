#include <RenderCommon.h>
#include <Init.h>
#include <Exception/Exception.h>

namespace OpenCarma
{
    Init::Init()
    {
        if (GL_TRUE != glfwInit())
            throw Commons::UnknownException("Can't init GLFW");       
    }


    Init::~Init()
    {
        glfwTerminate();
    }
}