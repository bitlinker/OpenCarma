#pragma once
#include <Common.h>
#include <Texture.h>
#include <map>
#include <set>

namespace OpenCarma
{
    class ITextureLoader
    {
    public:
        virtual TexturePtr load(const std::string& name);

        virtual ~ITextureLoader() {};
    };

    class TextureManager
    {
    public:
        TextureManager();
        ~TextureManager();

        TexturePtr getTexture(const string& name);

    private:
        typedef std::map<string, TextureWeakPtr> TTexturesMap;
        TTexturesMap m_textures;

        std::set<ITextureLoader> m_textureLoaders;
    };
}