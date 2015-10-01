#pragma once
#include <Common.h>
#include <RenderMaterial.h>
#include <Objects/Model.h>
#include <Render/RenderNode.h>
#include <Render.h>

#include <Render/BufferObject.h>
#include <Render/VertexArrayObject.h>

namespace OpenCarma
{
	// TODO: not a render node itself
    class StaticModel : public Commons::Render::RenderNode
    {
    public:
        StaticModel(const BRender::ModelPtr& model, Commons::Render::Render& render);
        virtual ~StaticModel();

        virtual void doRender(const glm::mat4& matrix);

    private:
        std::vector<Render::RenderMaterialPtr> m_materials;
		Commons::Render::BufferObject m_vertBuf;
		Commons::Render::BufferObject m_UVBuf;
		Commons::Render::BufferObject m_indexBuf;
		Commons::Render::VertexArrayObject m_vao;
        uint32_t m_numIndices;
    };

    typedef std::shared_ptr<StaticModel> StaticModelPtr;
}