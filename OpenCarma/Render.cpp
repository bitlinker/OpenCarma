#include <Render.h>
#include <Exception.h>

namespace OpenCarma
{
    Render::Render()
        : m_window()
        , m_texManager()
    {
        //glfwGetPrimaryMonitor()
        m_window = std::shared_ptr<GLFWwindow>(glfwCreateWindow(640, 480, "Title", NULL, NULL), glfwDestroyWindow);
        if (m_window == nullptr)
            throw new UnknownException("Can't create GLFW window");
        glfwMakeContextCurrent(m_window.get());

        //glfwSetKeyCallback(m_window.get(), );        
    }

    void Render::render()
    {
        // TODO: rm
        static TexturePtr tex = getTextureManager().getTexture("BGLSIDE.PIX");

        glEnable(GL_TEXTURE_2D);
        if (tex)
            tex->bind();


        float ratio;
        int width, height;
        glfwGetFramebufferSize(m_window.get(), &width, &height);
        ratio = width / (float)height;
        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glRotatef((float)glfwGetTime() * 50.f, 0.f, 0.f, 1.f);

        glBegin(GL_TRIANGLE_STRIP);

        glTexCoord2f(0.F, 0.F);
        glVertex3f(-0.5f, -0.5f, 0.f);

        glTexCoord2f(0.F, 1.F);
        glVertex3f(-0.5f, 0.5f, 0.f);

        glTexCoord2f(1.F, 0.F);
        glVertex3f(0.5f, -0.5f, 0.f);

        glTexCoord2f(1.F, 1.F);
        glVertex3f(0.5f, 0.5f, 0.f);

        glEnd();

        glDisable(GL_TEXTURE_2D);
    }

    bool Render::tick(float fTimeDelta)
    {
        if (glfwWindowShouldClose(m_window.get()))
            return false;
        
        /* TODO Render here */
        render();

        glfwSwapBuffers(m_window.get());
        glfwPollEvents();

        return true;
    }

    TextureManager& Render::getTextureManager()
    {
        return m_texManager;
    }


    Render::~Render()
    {
    }
}