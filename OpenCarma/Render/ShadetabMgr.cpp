#include <ShadetabMgr.h>

#include <Streams/IOStream.h>
#include <Logger/Log.h>
#include <Exception/Exception.h>

#include <Serialization/PixmapSerializer.h>

using namespace Commons;
using namespace Commons::Render;
using namespace OpenCarma::BRender;

namespace OpenCarma
{
    namespace Render
    {
		ShadetabMgr::ShadetabMgr(Context* context, Filesystem* fs)
			: mContext(context)
			, mFs(fs)
			, mResMgr()
		{
			// TODO: proper init check; fill data
			mIdentityShadetab = std::make_shared<Pixmap>(Pixmap::BR_PMT_INDEX_8, 256, 1, 256);
		}

		bool ShadetabMgr::loadShadetabPack(const std::string& packName)
		{
			std::vector<std::string> resNames;
			resNames.push_back(packName);
			return loadShadetabPack(resNames, packName);
		}

		bool loadShadetabPack(const std::vector<std::string>& resNames, const std::string& packName)
        {
			LOG_DEBUG("Loading shadetab pack %s", packName.c_str());
			IOStreamPtr strm = mFs->openResource(packName);
			if (!strm)
			{
				LOG_WARN("Can't get input stream for shadetab pack %s", packName.c_str());
				return false;
			}

			ResourceMgr<PixmapPtr>::ResourcePackPtr resPack(std::make_shared<ResourceMgr<PixmapPtr>::ResourcePack>());
			PixmapSerializer serializer;
			try
			{			
				serializer.read(strm, [this, &resPack](const PixmapPtr& pixmap) {
					// TODO: assert pixmap settings...
					resPack->addResource(pixmap->getName(), pixmap);
				});
			}
			catch (SerializationException se)
			{
				LOG_ERROR("SerializationException: %s", se.what());
				return false;
			}
			catch (IOException ioe)
			{
				LOG_ERROR("IOException: %s", ioe.what());
				return false;
			}

			mResMgr.addPack(packName, resPack);
			return true;
        }

        bool ShadetabMgr::unloadShadetabPack(const std::string& packName)
        {
			LOG_DEBUG("Unloading pixmap pack %s", packName.c_str());
			if (!mResMgr.removePack(packName))
			{
				LOG_WARN("Pack not found: %s", packName.c_str());
				return false;
			}
			return true;
        }

		PixmapPtr ShadetabMgr::getShadetab(const std::string& name)
		{
			LOG_DEBUG("Requesting shadetab %s", name.c_str());
			PixmapPtr shadetab;
			if (!mResMgr.getResource(name, shadetab))
			{
				LOG_WARN("Shadetab %s not found", name.c_str());
				return mIdentityShadetab;
			}
			return shadetab;
		}
    }
}
