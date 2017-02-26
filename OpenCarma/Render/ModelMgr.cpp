#include <ModelMgr.h>
#include <Streams/IOStream.h>
#include <Logger/Log.h>
#include <Exception/Exception.h>
#include <Serialization/ModelSerializer.h>

#include <algorithm>

using namespace Commons;
using namespace Commons::Render;
using namespace OpenCarma::BRender;

namespace OpenCarma
{
    namespace Render
    {
		ModelMgr::ModelMgr(Context* context, Filesystem* fs, MaterialMgr* materialMgr)
			: mContext(context)
            , mFs(fs)
			, mMaterialMgr(materialMgr)
		{
		}

        StaticModelPtr ModelMgr::loadModel(const ModelPtr& model)
        {
			// TODO: move here
            return std::make_shared<StaticModel>(model, mContext, mMaterialMgr);
        }

        bool ModelMgr::loadModelPack(const std::string& packName)
        {
            LOG_DEBUG("Loading model pack %s", packName.c_str());
            IOStreamPtr strm = mFs->openResource(packName);
            if (!strm)
			{
                LOG_WARN("Can't get input stream for model pack %s", packName.c_str());
                return false;
            }

			ResourceMgr<StaticModelPtr>::ResourcePackPtr resPack(std::make_shared<ResourceMgr<StaticModelPtr>::ResourcePack>());
            ModelSerializer serializer;
			try
			{
				serializer.read(strm, [this, &resPack](const ModelPtr& mdl) {
					StaticModelPtr staticModel = loadModel(mdl);
					resPack->addResource(mdl->getName(), staticModel);
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

        bool ModelMgr::unloadModelPack(const std::string& packName)
        {
            LOG_DEBUG("Unloading model pack %s", packName.c_str());
			if (!mResMgr.removePack(packName))
			{
				LOG_WARN("Pack not found: %s", packName.c_str());
				return false;
			}
			return true;
        }

		StaticModelPtr ModelMgr::getModel(const std::string& name)
		{
            LOG_DEBUG("Requesting model %s", name.c_str());
			StaticModelPtr mdl;
			if (!mResMgr.getResource(name, mdl))
			{
				LOG_WARN("Model %s not found", name.c_str());
				return nullptr;
				// TODO: return default? empty is ok...
			}
			return mdl;			
		}
    }
}
