#include <MaterialMgr.h>

#include <Serialization/MaterialSerializer.h>

#include <Exception/Exception.h>
#include <Logger/Log.h>

using namespace Commons;
using namespace Commons::Render;
using namespace OpenCarma::BRender;

namespace OpenCarma
{
    namespace Render
    {
		MaterialMgr::MaterialMgr(Commons::Render::Context* context, Filesystem* fs, TextureMgr* textureMgr)
			: mContext(context)
			, mFs(fs)
			, mTextureMgr(textureMgr)
			, mResMgr()
			, mDefaultMat(std::make_shared<Material>())
		{
			// TODO: init mDefaultMat
		}

		MaterialPtr MaterialMgr::loadMaterial(OpenCarma::BRender::MaterialPtr carmaMat)
		{
			// TODO
			// TODO: with palette & shadetab?
			//std::make_shared<Material>();
			return mDefaultMat;
		}

        bool MaterialMgr::loadMaterialPack(const std::string& packName)
        {
			LOG_DEBUG("Loading material pack %s", packName.c_str());
			IOStreamPtr strm = mFs->openResource(packName);
			if (!strm) 
			{
				LOG_WARN("Can't get input stream for material pack %s", packName.c_str());
				return false;
			}

			ResourceMgr<MaterialPtr>::ResourcePackPtr resPack(std::make_shared<ResourceMgr<MaterialPtr>::ResourcePack>());
			MaterialSerializer serializer;
			try
			{
				serializer.read(strm, [this, &resPack](const OpenCarma::BRender::MaterialPtr& brMat) {
					auto mat = loadMaterial(brMat);
					resPack->addResource(brMat->getName(), mat);
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

        bool MaterialMgr::unloadMaterialPack(const std::string& packName)
        {
			LOG_DEBUG("Unloading material pack %s", packName.c_str());
			if (!mResMgr.removePack(packName))
			{
				LOG_WARN("Pack not found: %s", packName.c_str());
				return false;
			}
			return true;
        }

		MaterialPtr MaterialMgr::getMaterial(const std::string& name)
		{
			LOG_DEBUG("Requesting material %s", name.c_str());
			MaterialPtr res;
			if (!mResMgr.getResource(name, res))
			{
				LOG_WARN("Material %s not found", name.c_str());
				return mDefaultMat;
			}
			return res;
		}
    }
}
