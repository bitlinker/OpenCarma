#pragma once
#include <Render/Context.h>

#include <Material.h>
#include <Filesystem.h>
#include <TextureMgr.h>
#include <ResourceMgr.h>

#include <Objects/Material.h>
#include <Objects/Pixmap.h>

namespace OpenCarma
{
    namespace Render
    {
        class MaterialMgr
        {
        public:
			MaterialMgr(Commons::Render::Context* context, Filesystem* fs, TextureMgr* textureMgr);
			virtual ~MaterialMgr() {};

            bool loadMaterialPack(const std::string& packName);
            bool unloadMaterialPack(const std::string& packName);

			// Not null!
			MaterialPtr getMaterial(const std::string& name);

		private:
			bool lazyLoadMainPalette();
			MaterialPtr loadMaterial(OpenCarma::BRender::MaterialPtr carmaMat);

        private:
			Commons::Render::Context* mContext;
			Filesystem* mFs;
			TextureMgr* mTextureMgr;
			ResourceMgr<MaterialPtr> mResMgr;
			MaterialPtr mDefaultMat;
			BRender::PixmapPtr mPalette;
        };

        typedef std::shared_ptr<MaterialMgr> MaterialMgrPtr;
    }
}
