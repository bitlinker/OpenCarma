#include <ModelMgr.h>
#include <Streams/IOStream.h>
#include <Logger/Log.h>
#include <Serialization/ModelSerializer.h>

using namespace Commons;
using namespace Commons::Render;
using namespace OpenCarma::BRender;

namespace OpenCarma
{
    namespace Render
    {
        // TODO: model pack instead of mgr? this will allow to load only needed data from actors
		ModelMgr::ModelMgr(Context* context, Filesystem* fs)
			: mContext(context)
            , mFs(fs)
		{
		}

        class ResPack
        {
        public:
        private:
        };

        std::map<std::string, std::shared_ptr<ResPack> > mPacks;

        StaticModelPtr ModelMgr::loadModel(const ModelPtr& model)
        {
            // TODO
            // MaterialMgr here...
            return std::make_shared<StaticModel>(model, mContext);
        }

        bool ModelMgr::registerModelPack(const std::string& packName)
        {
            LOG_DEBUG("Registering model pack %s", packName.c_str());
            IOStreamPtr strm = mFs->openResource(packName);
            if (!strm) {
                LOG_WARN("Can't get input stream for model pack %s", packName.c_str());
                return nullptr;
            }

            //mPacks.insert()

            ModelSerializer serializer;
            serializer.read(strm, [this](const ModelPtr& mdl) {
                loadModel(mdl); // TODO: add to pack
            });

            // TODO: catch?

            return true;
        }

        void ModelMgr::unregisterModelPack(const std::string& packName)
        {
            LOG_DEBUG("Unregistering model pack %s", packName.c_str());
            // TODO
        }

		StaticModelPtr ModelMgr::getModel(const std::string& name)
		{
            LOG_DEBUG("Requesting model %s", name.c_str());
			// TODO
			return nullptr;
		}
    }
}
