#pragma once
#include <Common.h>
#include <Texture.h>
#include <map>
#include <set>

namespace OpenCarma
{
    class TextureManager
    {
    public:
        TextureManager();
        ~TextureManager();

        TexturePtr getTexture(const string& name);

    private:
        typedef std::map<string, TextureWeakPtr> TTexturesMap;
        TTexturesMap m_textures;
    };
}