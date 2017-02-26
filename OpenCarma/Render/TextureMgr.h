#pragma once
#include <Render/Context.h>
#include <Render/Texture2d.h>

#include <ResourceMgr.h>
#include <Filesystem.h>
#include <map>

namespace OpenCarma
{
    namespace Render
    {
        class TextureMgr
        {
        public:
			TextureMgr(Commons::Render::Context* context, Filesystem* fs);
			virtual ~TextureMgr() {};

            bool loadPixelmapPack(const std::string& packName);
            bool unloadPixelmapPack(const std::string& packName);

			// Not null!
			Commons::Render::Texture2dPtr getTexture(const std::string& name);

        private:			
			Commons::Render::Context* mContext;
			Filesystem* mFs;
			ResourceMgr<Commons::Render::Texture2dPtr> mResMgr;
        };

        typedef std::shared_ptr<TextureMgr> TextureMgrPtr;
    }
}
