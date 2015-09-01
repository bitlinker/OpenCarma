#include <StaticModel.h>
#include <Render.h>

namespace OpenCarma
{
    StaticModel::StaticModel()
        : m_materials()
        , m_glVertBuf(0)
        , m_glUVBuf(0)
        , m_glIndexBuf(0)
        , m_numIndices(0)
        , m_glVao(0)
    {
        // TODO: sharedPtr
        glGenBuffers(1, &m_glVertBuf);
        glGenBuffers(1, &m_glUVBuf);
        glGenBuffers(1, &m_glIndexBuf);
        glGenVertexArrays(1, &m_glVao);
    }


    StaticModel::~StaticModel()
    {
        glDeleteVertexArrays(1, &m_glVao);
        glDeleteBuffers(1, &m_glVertBuf);
        glDeleteBuffers(1, &m_glUVBuf);
        glDeleteBuffers(1, &m_glIndexBuf);
    }

    void StaticModel::init(const BRender::ModelPtr& model, Render& render)
    {
        // TODO: model utils or custom methods
        auto mats = model->getMaterials();
        for (auto it = mats.begin(); it != mats.end(); ++it)
        {
            // TODO
            //render.getTextureManager().
            // TODO: load material                        
        }
        //m_materials[0]->set();

        auto vertices = model->getVertices();
        auto uvs = model->getUVs();
        auto faces = model->getFaces();
        auto facemats = model->getFaceMats();

        // Vertices
        glBindBuffer(GL_ARRAY_BUFFER, m_glVertBuf);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(BRender::Vertex3f), &vertices[0], GL_STATIC_DRAW);

        // UVs
        glBindBuffer(GL_ARRAY_BUFFER, m_glUVBuf);
        glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(BRender::Vertex2f), &uvs[0], GL_STATIC_DRAW);

        // TODO: normals

        // Indexes
        std::vector<uint16_t> indexes(faces.size() * 3);
        uint16_t* face = &indexes[0];
        for (auto it = faces.begin(); it != faces.end(); ++it)
        {
            *face++ = it->m_v[0];
            *face++ = it->m_v[1];
            *face++ = it->m_v[2];
        }

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_glIndexBuf);        
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexes.size() * sizeof(uint16_t), &indexes[0], GL_STATIC_DRAW);
        m_numIndices = faces.size() * 3;


        // Set up VAO
        glBindVertexArray(m_glVao);        
        
        // TODO: get attrib id from program
        // Vertexes
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, m_glVertBuf);        
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);        

        // UVs
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, m_glUVBuf);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, NULL);

        // Indexes
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_glIndexBuf);
    }

    void StaticModel::doRender(const glm::mat4& matrix)
    {
        glBindVertexArray(m_glVao); // TODO: wrapper

        //glEnableClientState(GL_VERTEX_ARRAY);
        //glVertexPointer(3, GL_FLOAT, 0, 0);

        glDrawElements(GL_TRIANGLES, m_numIndices, GL_UNSIGNED_SHORT, 0);

        glBindVertexArray(0);


        //glDisableClientState(GL_VERTEX_ARRAY);        

        //glBindBuffer(GL_ARRAY_BUFFER, 0);
        //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
}