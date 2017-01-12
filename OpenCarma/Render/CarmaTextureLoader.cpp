#include "CarmaTextureLoader.h"

namespace OpenCarma
{
    namespace Render
    {
        CarmaTextureLoader::CarmaTextureLoader()
        {
        }

        CarmaTextureLoader::~CarmaTextureLoader()
        {
        }

        // TODO: with palette?
        // TODO: throw or bool?
        void CarmaTextureLoader::registerPixelmapPack(const std::string& packName)
        {
            // TODO
        }

        void CarmaTextureLoader::unregisterPixelmapPack(const std::string& packName)
        {
            // TODO
        }

        bool CarmaTextureLoader::loadTexture(const std::string& name, const void* extra, const Commons::Render::TexturePtr& texture)
        {
            // TODO
            return false;
        }
    }
}
