#pragma once
#include <Common.h>
#include <glfw/glfw3.h>

// TODO: move
#include <Objects/Pixmap.h>
#include <Objects/Palette.h>

namespace OpenCarma
{
    class Texture
    {
    public:
        Texture();
        ~Texture();

        void initFromPixelmap(const BRender::PixmapPtr& pixelmap, const BRender::PalettePtr& palette);

        void bind();
        void unbind();

    private:
        GLuint m_tex;
    };

    typedef std::shared_ptr<Texture> TexturePtr;
}