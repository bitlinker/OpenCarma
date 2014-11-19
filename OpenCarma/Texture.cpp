#include <Texture.h>
#include <cassert>

namespace OpenCarma
{
    Texture::Texture()
        : m_tex(0)
    {
        glGenTextures(1, &m_tex);
    }


    Texture::~Texture()
    {
        glDeleteTextures(1, &m_tex);
    }

    void Texture::initFromPixelmap(const BRender::PixmapPtr& pixelmap, const BRender::PalettePtr& palette)
    {
        assert(pixelmap);
        assert(palette);

        bind();

        // TODO: helper
        uint32_t width = pixelmap->getWidth();
        uint32_t height = pixelmap->getHeight();

        const uint8_t* src = &pixelmap->getPixels()[0];
        std::vector<uint32_t> rgbPixmap(width * height);  // RGBA

        for (uint32_t y = 0; y < height; ++y)
        {
            uint32_t* dst = &rgbPixmap[y * width];

            for (uint32_t x = 0; x < width; ++x)
            {
                const uint32_t srcColor = palette->getColor(*src++);
                const uint8_t* srcChannel = reinterpret_cast<const uint8_t*>(&srcColor);
                uint8_t *dstChannel = reinterpret_cast<uint8_t*>(dst++);

                dstChannel[0] = srcChannel[1]; // B
                dstChannel[1] = srcChannel[2]; // G
                dstChannel[2] = srcChannel[3]; // R
                dstChannel[3] = srcChannel[0]; // A
            }
        }

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, pixelmap->getWidth(), pixelmap->getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, &rgbPixmap[0]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }

    void Texture::bind()
    {
        glBindTexture(GL_TEXTURE_2D, m_tex);
    }

    void Texture::unbind()
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}