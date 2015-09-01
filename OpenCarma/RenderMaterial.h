#pragma once
#include <RenderCommon.h>
#include <ShaderProgram.h>
#include <Texture.h>

namespace OpenCarma
{
    class RenderMaterial
    {
    public:
        RenderMaterial();
        ~RenderMaterial();

        void set();
        // TODO: store shader, shader state(uniform values), textures

    private:
        ShaderProgramPtr m_shader;
        std::vector<TexturePtr> m_textures;
    };

    typedef std::shared_ptr<RenderMaterial> RenderMaterialPtr;
}