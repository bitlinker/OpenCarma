#pragma once
#include <Render/Context.h>
#include <StaticModel.h>
#include <map>

namespace OpenCarma
{
    namespace Render
    {
        class ModelMgr
        {
        public:
			ModelMgr(Commons::Render::Context* context);
			virtual ~ModelMgr() {};

            void registerModelPack(const std::string& packName);
            void unregisterModelPack(const std::string& packName);

			StaticModelPtr getModel(const std::string& name);

        private:
            //typedef std::map<std::string, Commons::Render::Texture2dWeakPtr> TTexturesMap;
            //TTexturesMap m_textures;
			Commons::Render::Context* mContext;
        };

        typedef std::shared_ptr<ModelMgr> ModelMgrPtr;
    }
}
