#include <ActorMgr.h>
#include <Serialization/ActorSerializer.h>

using namespace Commons::Render;
using namespace OpenCarma::BRender;

namespace OpenCarma
{
    namespace Render
    {
		ActorMgr::ActorMgr(Context* context)
			: mContext(context)
		{
		}

        // TODO: with palette?
        // TODO: throw or bool?
        void ActorMgr::registerActorPack(const std::string& packName)
        {
            // TODO
        }

        void ActorMgr::unregisterActorPack(const std::string& packName)
        {
            // TODO
        }

		RenderNodePtr ActorMgr::inflateActorTree(const std::string& name)
		{
			ActorSerializer actorSerializer;
			ActorPtr actor = actorSerializer.read();
			//actor->getModel();
			// TODO: case insensitive compare
			// TODO: impl
			return std::make_shared<RenderNode>(name);
		}
    }
}
