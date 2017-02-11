#pragma once
#include <Render/Context.h>
#include <Render/Texture2d.h>
#include <map>

namespace OpenCarma
{
    namespace Render
    {
        class TextureMgr
        {
        public:
			TextureMgr(Commons::Render::Context* context);
			virtual ~TextureMgr() {};

            void registerPixelmapPack(const std::string& packName);
            void unregisterPixelmapPack(const std::string& packName);

			Commons::Render::Texture2dPtr getTexture(const std::string& name);

        private:
            typedef std::map<std::string, Commons::Render::Texture2dWeakPtr> TTexturesMap;
            TTexturesMap m_textures;
			Commons::Render::Context* mContext;
        };

        typedef std::shared_ptr<TextureMgr> TextureMgrPtr;
    }
}
