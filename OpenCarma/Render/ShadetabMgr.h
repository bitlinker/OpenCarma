#pragma once
#include <Render/Context.h>

#include <Objects/Pixmap.h>

#include <ResourceMgr.h>
#include <Filesystem.h>
#include <map>
#include <vector>

namespace OpenCarma
{
    namespace Render
    {
        class ShadetabMgr
        {
        public:
			ShadetabMgr(Commons::Render::Context* context, Filesystem* fs);
			virtual ~ShadetabMgr() {};

            bool loadShadetabPack(const std::string& packName);
			bool loadShadetabPack(const std::vector<std::string>& resNames, const std::string& packName);
            bool unloadShadetabPack(const std::string& packName);

			// Not null!
			BRender::PixmapPtr getShadetab(const std::string& name);

        private:			
			Commons::Render::Context* mContext;
			Filesystem* mFs;
			ResourceMgr<BRender::PixmapPtr> mResMgr;
			BRender::PixmapPtr mIdentityShadetab;
        };

        typedef std::shared_ptr<ShadetabMgr> ShadetabMgrPtr;
    }
}
