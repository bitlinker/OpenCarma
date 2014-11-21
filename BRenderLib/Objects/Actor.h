#pragma once
#include <Common.h>
#include <Objects/ChunkHeader.h>

namespace OpenCarma
{
	namespace BRender
	{
        class Actor;
        typedef std::shared_ptr<Actor> ActorPtr;
        typedef std::weak_ptr<Actor> ActorWeakPtr;

        class BR_API Actor
		{
            friend class ActorSerializer;
		public:
			Actor();
			~Actor();

            bool isValid() const;
            
        private:
            ActorNameChunk m_header;
            ActorMatrixChunk m_matrix;
            ActorMaterialChunk m_materials;
            ActorModelChunk m_models;
            ActorEmptyChunk m_empty;
            ActorBBoxChunk m_bbox;

            ActorWeakPtr m_parent;
            std::vector<ActorPtr> m_children;
		};
	}
}