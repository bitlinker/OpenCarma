#include <TextureMgr.h>

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
		TextureMgr::TextureMgr(Context* context, Filesystem* fs)
			: mContext(context)
			, mFs(fs)
			, mResMgr()
		{
			// TODO: load palettes
		}

        // TODO: with palette?
        bool TextureMgr::loadPixelmapPack(const std::string& packName)
        {
			LOG_DEBUG("Loading pixmap pack %s", packName.c_str());
			IOStreamPtr strm = mFs->openResource(packName);
			if (!strm)
			{
				LOG_WARN("Can't get input stream for pixmap pack %s", packName.c_str());
				return false;
			}

			ResourceMgr<Texture2dPtr>::ResourcePackPtr resPack(std::make_shared<ResourceMgr<Texture2dPtr>::ResourcePack>());
			PixmapSerializer serializer;

			try
			{			
				serializer.read(strm, [this, &resPack](const PixmapPtr& pixmap) {
					// TODO
					resPack->addResource(pixmap->getName(), Texture2dPtr(new Texture2d(mContext))); // TODO: init
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

        bool TextureMgr::unloadPixelmapPack(const std::string& packName)
        {
			LOG_DEBUG("Unloading pixmap pack %s", packName.c_str());
			if (!mResMgr.removePack(packName))
			{
				LOG_WARN("Pack not found: %s", packName.c_str());
				return false;
			}
			return true;
        }

		Texture2dPtr TextureMgr::getTexture(const std::string& name)
		{
			LOG_DEBUG("Requesting pixmap %s", name.c_str());
			Texture2dPtr texture;
			if (!mResMgr.getResource(name, texture))
			{
				LOG_WARN("Texture %s not found", name.c_str());
				return nullptr;
				// TODO: return default
			}
			return texture;
		}
    }
}
