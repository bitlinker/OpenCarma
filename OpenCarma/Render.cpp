#include <Render.h>
#include <Exception.h>

Render::Render()
{
    //glfwGetPrimaryMonitor()
    m_window = std::shared_ptr<GLFWwindow>(glfwCreateWindow(640, 480, "Title", NULL, NULL), glfwDestroyWindow);
    if (m_window == nullptr)
        throw new UnknownException("Can't create GLFW window");
    glfwMakeContextCurrent(m_window.get());

    //glfwSetKeyCallback(m_window.get(), );
}

void render(GLFWwindow* window)
{
    float ratio;
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    ratio = width / (float)height;
    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotatef((float)glfwGetTime() * 50.f, 0.f, 0.f, 1.f);
    glBegin(GL_TRIANGLES);
    glColor3f(1.f, 0.f, 0.f);
    glVertex3f(-0.6f, -0.4f, 0.f);
    glColor3f(0.f, 1.f, 0.f);
    glVertex3f(0.6f, -0.4f, 0.f);
    glColor3f(0.f, 0.f, 1.f);
    glVertex3f(0.f, 0.6f, 0.f);
    glEnd();    
}

bool Render::tick(float fTimeDelta)
{
    if (glfwWindowShouldClose(m_window.get()))
        return false;
    
    /* TODO Render here */
    render(m_window.get());

    glfwSwapBuffers(m_window.get());
    glfwPollEvents();
    
    return true;
}


Render::~Render()
{
}
