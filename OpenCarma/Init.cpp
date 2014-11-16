#include <Init.h>
#include <Exception.h>
#include <glfw/glfw3.h>


Init::Init()
{
    if (GL_TRUE != glfwInit())
        throw UnknownException("Can't init glfw");
}


Init::~Init()
{
    glfwTerminate();
}
