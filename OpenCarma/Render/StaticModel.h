#pragma once
#include <Common.h>
#include <Material.h>
#include <Objects/Model.h>
#include <Render/RenderNode.h>
#include <Render/BufferObject.h>
#include <Render/VertexArrayObject.h>

namespace OpenCarma
{
	namespace Render
	{
		class Render;

		class StaticModel : public Commons::Render::IRenderable
		{
		public:
			StaticModel(const BRender::ModelPtr& model, Commons::Render::Context* context);
			virtual ~StaticModel();

            virtual void render(const glm::mat4& matrix);

		private:
			std::vector<MaterialPtr> m_materials;
			Commons::Render::BufferObject m_vertBuf;
			Commons::Render::BufferObject m_UVBuf;
			Commons::Render::BufferObject m_indexBuf;
			Commons::Render::VertexArrayObject m_vao;
			uint32_t m_numIndices;

            Commons::Render::Context* mContext;
		};

		typedef std::shared_ptr<StaticModel> StaticModelPtr;
	}
}