#include <MaterialMgr.h>

using namespace Commons::Render;

namespace OpenCarma
{
    namespace Render
    {
		MaterialMgr::MaterialMgr(Context* context)
			: mContext(context)
		{
			// TODO: load palettes
		}

        // TODO: with palette?
        // TODO: throw or bool?
        void MaterialMgr::registerMaterialPack(const std::string& packName)
        {
            // TODO
        }

        void MaterialMgr::unregisterMaterialPack(const std::string& packName)
        {
            // TODO
        }

		MaterialPtr MaterialMgr::getMaterial(const std::string& name)
		{
			// TODO
			return nullptr;
		}
    }
}
