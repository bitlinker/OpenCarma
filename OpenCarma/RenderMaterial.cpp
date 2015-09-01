#include "RenderMaterial.h"

namespace OpenCarma
{
    RenderMaterial::RenderMaterial()
    {
    }


    RenderMaterial::~RenderMaterial()
    {
    }

    void RenderMaterial::set()
    {
        if (m_shader)
        {
            m_shader->use();

            // TODO: set states
            //m_shader->setUniformMatrix()
        }

        for (auto tex : m_textures)
        {
            tex->bind();
        }
    }
}