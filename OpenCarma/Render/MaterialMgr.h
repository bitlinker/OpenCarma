#pragma once
#include <Render/Context.h>
#include <Material.h>
#include <map>

namespace OpenCarma
{
    namespace Render
    {
        class MaterialMgr
        {
        public:
			MaterialMgr(Commons::Render::Context* context);
			virtual ~MaterialMgr() {};

            void registerMaterialPack(const std::string& packName);
            void unregisterMaterialPack(const std::string& packName);

			MaterialPtr getMaterial(const std::string& name);

        private:
            //typedef std::map<std::string, Commons::Render::Texture2dWeakPtr> TTexturesMap;
            //TTexturesMap m_textures;
			Commons::Render::Context* mContext;
        };

        typedef std::shared_ptr<MaterialMgr> MaterialMgrPtr;
    }
}
