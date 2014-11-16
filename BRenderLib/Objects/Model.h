#pragma once
#include <Common.h>
#include <Objects/ChunkHeader.h>

namespace OpenCarma
{
	namespace BRender
	{
		class Model
		{
            friend class ModelSerializer;
		public:
			Model();
			~Model();

            bool isValid() const;

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