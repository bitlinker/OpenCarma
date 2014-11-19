#pragma once
#include <Common.h>
#include <Texture.h>
#include <Objects/Pixmap.h>
#include <Objects/Palette.h>
#include <map>

namespace OpenCarma
{
    class TextureManager
    {
    public:
        TextureManager();
        ~TextureManager();

        void load(const BRender::PixmapPtr& pixmap, const BRender::PalettePtr& palette);
        void load(const std::vector<BRender::PixmapPtr>& pixmaps, const BRender::PalettePtr& palette);

        TexturePtr getTexture(const string& name);
        void clear();

    private:
        typedef std::map<string, TexturePtr> TTexturesMap;
        TTexturesMap m_textures;
    };
}