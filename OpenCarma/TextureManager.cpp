#include <TextureManager.h>
#include <cassert>

namespace OpenCarma
{
    TextureManager::TextureManager()
    {
    }


    TextureManager::~TextureManager()
    {
    }

    void TextureManager::load(const BRender::PixmapPtr& pixmap, const BRender::PalettePtr& palette)
    {
        assert(pixmap);
        assert(palette);

        TexturePtr texture = std::make_shared<Texture>();
        texture->initFromPixelmap(pixmap, palette);
        m_textures[pixmap->getName()] = texture;
    }

    void TextureManager::load(const std::vector<BRender::PixmapPtr>& pixmaps, const BRender::PalettePtr& palette)
    {
        assert(palette);

        for each (auto pixmap in pixmaps)
            load(pixmap, palette);
    }

    TexturePtr TextureManager::getTexture(const string& name)
    {
        TTexturesMap::const_iterator it = m_textures.find(name);
        if (it != m_textures.end())
            return it->second;

        return nullptr;
    }

    void TextureManager::clear()
    {
        m_textures.clear();
    }
}