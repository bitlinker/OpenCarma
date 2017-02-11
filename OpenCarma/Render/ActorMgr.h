#pragma once
#include <Render/Context.h>
#include <map>

namespace OpenCarma
{
    namespace Render
    {
        class ActorMgr
        {
        public:
			ActorMgr(Commons::Render::Context* context);
			virtual ~ActorMgr() {};

            void registerActorPack(const std::string& packName);
            void unregisterActorPack(const std::string& packName);

			Commons::Render::RenderNodePtr inflateActorTree(const std::string& name);

        private:
            //typedef std::map<std::string, Commons::Render::Texture2dWeakPtr> TTexturesMap;
            //TTexturesMap m_textures;
			Commons::Render::Context* mContext;
        };

        typedef std::shared_ptr<ActorMgr> ActorMgrPtr;
    }
}
