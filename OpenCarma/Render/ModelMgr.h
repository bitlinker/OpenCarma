#pragma once
#include <Render/Context.h>
#include <Filesystem.h>
#include <ResourceMgr.h>
#include <StaticModel.h>
#include <MaterialMgr.h>

#include <map>

namespace OpenCarma
{
    namespace Render
    {
        class ModelMgr
        {
        public:
			ModelMgr(Commons::Render::Context* context, Filesystem* fs, MaterialMgr* materialMgr);
			virtual ~ModelMgr() {};

            bool loadModelPack(const std::string& packName);
            bool unloadModelPack(const std::string& packName);

			// Nullable
			StaticModelPtr getModel(const std::string& name);

        private:
            StaticModelPtr loadModel(const OpenCarma::BRender::ModelPtr& model);

        private:
			ResourceMgr<StaticModelPtr> mResMgr;
			// TODO: shared pointers?
			Commons::Render::Context* mContext;
            Filesystem* mFs;
			MaterialMgr* mMaterialMgr;
        };

        typedef std::shared_ptr<ModelMgr> ModelMgrPtr;
    }
}
