#include <StaticModel.h>
#include <Render/ScopeBind.h>

namespace OpenCarma
{
	namespace Render
	{
		StaticModel::StaticModel(const BRender::ModelPtr& model, Commons::Render::Context* context, MaterialMgr* materialMgr)
			: m_materials()
			, m_vertBuf(GL_ARRAY_BUFFER)
			, m_UVBuf(GL_ARRAY_BUFFER)
			, m_indexBuf(GL_ELEMENT_ARRAY_BUFFER)
			, m_vao()
			, m_numIndices(0)
			, mContext(context)
		{
			auto mats = model->getMaterials();
			m_materials.reserve(mats.size());
			for (auto it = mats.begin(); it != mats.end(); ++it)
			{
				m_materials.push_back(materialMgr->getMaterial(*it));
			}

			auto vertices = model->getVertices();
			auto uvs = model->getUVs();
			auto faces = model->getFaces();
			auto facemats = model->getFaceMats();

			// TODO: iterate facemats, build buffers for each
			// TODO: build normals
			// TODO: vertex structure

			// Vertices
			m_vertBuf.setData(vertices.size() * sizeof(BRender::Model::Vertex3f), &vertices[0], GL_STATIC_DRAW);

			// UVs
			m_UVBuf.setData(uvs.size() * sizeof(BRender::Model::Vertex2f), &uvs[0], GL_STATIC_DRAW);

			// TODO: normals

			// Indexes
			std::vector<uint16_t> indexes(faces.size() * 3);
			uint16_t* face = &indexes[0];
			for (auto it = faces.begin(); it != faces.end(); ++it)
			{
				*face++ = it->mV[0];
				*face++ = it->mV[1];
				*face++ = it->mV[2];
			}

			m_indexBuf.setData(indexes.size() * sizeof(uint16_t), &indexes[0], GL_STATIC_DRAW);
			m_numIndices = faces.size() * 3;


			// Set up VAO
			{
				Commons::Render::ScopeBind bind(m_vao);
				// TODO: get attrib id from program
				// Vertexes
				glEnableVertexAttribArray(0);
				m_vertBuf.bind();
				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

				// UVs
				glEnableVertexAttribArray(1);
				m_UVBuf.bind();
				glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, NULL);

				// Indexes
				m_indexBuf.bind();
			}
		}


		StaticModel::~StaticModel()
		{
		}


		void StaticModel::render(const glm::mat4& matrix)
		{
			Commons::Render::ScopeBind bind(m_vao);

			//auto shaderProg = m_render.getPlainShaderProgram();
			//shaderProg->setMVP(matrix);
			//shaderProg->setTex1Sampler(0);
			//shaderProg->use(); // TODO: in materials?

            //m_renderPtr->drawElements();

			// TODO: set materials...

            // TODO: context
			glDrawElements(GL_TRIANGLES, m_numIndices, GL_UNSIGNED_SHORT, 0);
		}
	}
}