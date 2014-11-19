#pragma once

#include <memory>
#include <glfw/glfw3.h>
#include <glm/glm.hpp>
#include <TextureManager.h>

namespace OpenCarma
{
    class Render
    {
    public:
        Render();
        ~Render();

        bool tick(float fTimeDelta);
        void render();

        // TODO: replace
        TextureManager& getTextureManager();

    private:
        std::shared_ptr<GLFWwindow> m_window;
        TextureManager m_texManager;
    };
}