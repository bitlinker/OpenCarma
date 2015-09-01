#pragma once
#include <Common.h>
#include <RenderMaterial.h>
#include <Objects/Model.h>
#include <RenderNode.h>
#include <Render.h>

namespace OpenCarma
{
    // Static model
    class StaticModel : public RenderNode
    {
    public:
        StaticModel();
        virtual ~StaticModel();

        void init(const BRender::ModelPtr& model, Render& render);

        virtual void doRender(const glm::mat4& matrix);

    private:
        std::vector<RenderMaterialPtr> m_materials;
        GLuint m_glVertBuf;
        GLuint m_glUVBuf;
        GLuint m_glIndexBuf;
        GLuint m_glVao;
        uint32_t m_numIndices;
    };

    typedef std::shared_ptr<StaticModel> StaticModelPtr;
}