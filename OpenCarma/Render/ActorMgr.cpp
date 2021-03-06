#include <ActorMgr.h>
#include <Streams/IOStream.h>
#include <Logger/Log.h>
#include <Serialization/ActorSerializer.h>
#include <algorithm>

#include <Render/StaticModel.h>

using namespace Commons;
using namespace Commons::Render;
using namespace OpenCarma::BRender;

namespace OpenCarma
{
    namespace Render
    {
		ActorMgr::ActorMgr(Context* context, Filesystem* fs, ModelMgr* modelMgr)
			: mContext(context)
            , mFs(fs)
            , mModelMgr(modelMgr)
		{
		}

		static glm::mat4 TranslateMatrix(const Matrix34& matrix)
		{
			// TODO: check
			glm::mat4 result;
			for (uint32_t y = 0; y < 3; ++y)
			{
				for (uint32_t x = 0; x < 3; ++x)
				{
					result[y][x] = matrix.mValue[x + y * 3];
				}
			}
			result[3][0] = matrix.mValue[10];
			result[3][1] = matrix.mValue[11];
			result[3][2] = matrix.mValue[12];
			result[3][3] = 1.F;
			return result;
		}

		static AABB TranslateBBox(const BBox& bbox)
		{
			glm::vec3 mins(bbox.mPos[0], bbox.mPos[1], bbox.mPos[2]);
			glm::vec3 maxs = mins + glm::vec3(bbox.mSize[0], bbox.mSize[1], bbox.mSize[2]);
			return AABB(mins, maxs);
		}

		RenderNodePtr ActorMgr::actor2Node(const ActorPtr& actor)
		{
			RenderNodePtr node = std::make_shared<RenderNode>(actor->getName());
			node->setTranslation(TranslateMatrix(actor->getTransform()));
			node->setBBox(TranslateBBox(actor->getBbox()));
			actor->getFlags(); // TODO: check
			actor->getMaterial(); // TODO: load?

            const auto model = actor->getModel();
            if (!model.empty())
            {
                StaticModelPtr staticModel = mModelMgr->getModel(model);
                node->setRenderable(staticModel);
            }
			
			auto children = actor->getChildren();
			std::for_each(children.begin(), children.end(), [this, &node](const ActorPtr& child) {
				node->attachChild(actor2Node(child));
			});
			return node;
		}

		RenderNodePtr ActorMgr::inflateActorTree(const std::string& name)
		{
            LOG_DEBUG("Requesting actor %s", name.c_str());
            IOStreamPtr strm = mFs->openResource(name);
            if (!strm) {
                LOG_WARN("Can't get input stream for actor %s", name.c_str());
                return nullptr;
            }
            ActorSerializer actorSerializer;
            ActorPtr actor = actorSerializer.read(strm);
			return actor2Node(actor);
		}
    }
}
