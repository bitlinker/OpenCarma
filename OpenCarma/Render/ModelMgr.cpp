#include <ModelMgr.h>

using namespace Commons::Render;

namespace OpenCarma
{
    namespace Render
    {
		ModelMgr::ModelMgr(Context* context)
			: mContext(context)
		{
			// TODO: load palettes
		}

        // TODO: with palette?
        // TODO: throw or bool?
        void ModelMgr::registerModelPack(const std::string& packName)
        {
            // TODO
        }

        void ModelMgr::unregisterModelPack(const std::string& packName)
        {
            // TODO
        }

		StaticModelPtr ModelMgr::getModel(const std::string& name)
		{
			// TODO
			return nullptr;
		}
    }
}
