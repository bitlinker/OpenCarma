#pragma once
#include <Render/Context.h>
#include <Filesystem.h>
#include <StaticModel.h>

#include <map>

namespace OpenCarma
{
    namespace Render
    {
        class ModelMgr
        {
        public:
			ModelMgr(Commons::Render::Context* context, Filesystem* fs);
			virtual ~ModelMgr() {};

            bool registerModelPack(const std::string& packName);
            void unregisterModelPack(const std::string& packName);

			StaticModelPtr getModel(const std::string& name);

        private:
            StaticModelPtr loadModel(const OpenCarma::BRender::ModelPtr& model);

        private:
            //typedef std::map<std::string, Commons::Render::Texture2dWeakPtr> TTexturesMap;
            //TTexturesMap m_textures;
			Commons::Render::Context* mContext;
            Filesystem* mFs;
        };

        typedef std::shared_ptr<ModelMgr> ModelMgrPtr;
    }
}
