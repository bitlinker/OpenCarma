#pragma once
#include <Render/Context.h>
#include <Render/Texture2d.h>

#include <Objects/Pixmap.h>

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

			// TODO: separate?
			// Palette management
			bool loadPalettePack(const std::string& packName);
			// Can be null
			BRender::PixmapPtr getPalette(const std::string& name);

            bool loadPixelmapPack(const std::string& packName);
            bool unloadPixelmapPack(const std::string& packName);

			// Not null!
			// TODO: with shadetab?
			Commons::Render::Texture2dPtr getTexture(const std::string& name);

        private:			
			// TODO: cache pixmaps here
			// Textures cached not here
			Commons::Render::Context* mContext;
			Filesystem* mFs;
			ResourceMgr<Commons::Render::Texture2dPtr> mResMgr;
			// TODO: separate?
			ResourceMgr<BRender::PixmapPtr>::ResourcePack mPalettesPack;
        };

        typedef std::shared_ptr<TextureMgr> TextureMgrPtr;
    }
}
