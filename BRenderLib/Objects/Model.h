#pragma once
#include <Common.h>
#include <Objects/ChunkHeader.h>

namespace OpenCarma
{
	namespace BRender
	{
		class BR_API Model
		{
            friend class ModelSerializer;
		public:
			Model();
			~Model();

            bool isValid() const;

            const std::string& getName() const { return m_header.mName; }
            const std::vector<Vertex3f>& getVertices() const { return m_vertices.m_vertices; }
            const std::vector<Vertex2f>& getUVs() const { return m_uv.m_uv; }
            const std::vector<Face>& getFaces() const { return m_faces.m_faces; }
            const std::vector<std::string>& getMaterials() const { return m_materials.m_materials; }
            const std::vector<uint16_t>& getFaceMats() const { return m_faceMats.m_faceMats; }

        private:
            ModelHeadChunk m_header;
            ModelVerticesChunk m_vertices;
            ModelUVsChunk m_uv;
            ModelFacesChunk m_faces;
            ModelMaterialsChunk m_materials;
            ModelFaceMaterialsChunk m_faceMats;
		};

        typedef std::shared_ptr<Model> ModelPtr;
	}
}