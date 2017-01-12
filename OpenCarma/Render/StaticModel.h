#pragma once
#include <Common.h>
#include <RenderMaterial.h>
#include <Objects/Model.h>
#include <Render/RenderNode.h>
#include <Render/BufferObject.h>
#include <Render/VertexArrayObject.h>

namespace OpenCarma
{
	namespace Render
	{
		class Render;

		class StaticModel
		{
		public:
			StaticModel(const BRender::ModelPtr& model, Render* renderPtr);
			~StaticModel();

			void render(const glm::mat4& matrix);

		private:
			std::vector<RenderMaterialPtr> m_materials;
			Commons::Render::BufferObject m_vertBuf;
			Commons::Render::BufferObject m_UVBuf;
			Commons::Render::BufferObject m_indexBuf;
			Commons::Render::VertexArrayObject m_vao;
			uint32_t m_numIndices;

			Render* m_renderPtr; // TODO: rm?
		};

		typedef std::shared_ptr<StaticModel> StaticModelPtr;


		// TODO: separate file
		class StaticModelNode : public Commons::Render::RenderNode
		{
		public:
			StaticModelNode(const StaticModelPtr& model);
			virtual ~StaticModelNode();

			virtual void doRender(const glm::mat4& matrix);

		private:
			StaticModelPtr m_node;
		};
        typedef std::shared_ptr<StaticModelNode> StaticModelNodePtr;
	}
}