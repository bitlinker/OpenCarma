#pragma once
#include <Render/ITextureLoader.h>
#include <map>

namespace OpenCarma
{
    namespace Render
    {
        class CarmaTextureLoader : public Commons::Render::ITextureLoader
        {
        public:
            CarmaTextureLoader();
            virtual ~CarmaTextureLoader();

            void registerPixelmapPack(const std::string& packName);
            void unregisterPixelmapPack(const std::string& packName);

            virtual bool loadTexture(const std::string& name, const void* extra, const Commons::Render::TexturePtr& texture);

        private:
            typedef std::map<std::string, Commons::Render::TextureWeakPtr> TTexturesMap;
            TTexturesMap m_textures;
        };

        typedef std::shared_ptr<CarmaTextureLoader> CarmaTextureLoaderPtr;
    }
}
