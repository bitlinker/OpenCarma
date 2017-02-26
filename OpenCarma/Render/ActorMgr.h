#pragma once
#include <Render/Context.h>
#include <Render/ModelMgr.h>
#include <Filesystem.h>

#include <Objects/Actor.h>

#include <map>

namespace OpenCarma
{
    namespace Render
    {
        class ActorMgr
        {
        public:
			ActorMgr(Commons::Render::Context* context, Filesystem* fs, ModelMgr* modelMgr);
			virtual ~ActorMgr() {};

            Commons::Render::RenderNodePtr inflateActorTree(const std::string& name);

		private:
			Commons::Render::RenderNodePtr actor2Node(const OpenCarma::BRender::ActorPtr& actor);

        private:
			Commons::Render::Context* mContext;
            Filesystem* mFs;
            ModelMgr* mModelMgr;
        };

        typedef std::shared_ptr<ActorMgr> ActorMgrPtr;
    }
}
