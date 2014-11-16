#pragma once

#include <memory>
#include <glfw/glfw3.h>
#include <glm/glm.hpp>

class Render
{
public:
    Render();
    ~Render();

    bool tick(float fTimeDelta);

private:
    std::shared_ptr<GLFWwindow> m_window;
};
