#include <Objects/ChunkHeader.h>
#include <EndianStreamReader.h>
#include <Exception/Exception.h>


namespace OpenCarma
{
    namespace BRender
    {
        ChunkHeader::ChunkHeader() :
            m_magic(0),
            m_size(0)
        {
        }

        void ChunkHeader::read(EndianStreamReader& reader)
        {
            if (!reader.isEOF())
                m_magic = reader.readUInt32();
            if (!reader.isEOF())
                m_size = reader.readUInt32();
            // TODO: type the chunk magic, size & offset here...
            //printf("Magic: %x(%d), len: %d at: %d\n", m_magic, m_magic, m_size, reader.tell());
        }


        FileHeaderChunk::FileHeaderChunk()
            : m_version1(0)
            , m_version2(0)
        {
        }

        void FileHeaderChunk::read(EndianStreamReader& reader)
        {
            m_version1 = reader.readUInt32();
            m_version2 = reader.readUInt32();
        }

        TextureHeadChunk::TextureHeadChunk()
            : m_pixelFormat(0)
            , m_stride(0)
            , m_width(0)
            , m_height(0)
            , m_offsetX(0)
            , m_offsetY(0)
            , m_name()
        {
        }

        void TextureHeadChunk::read(EndianStreamReader& reader)
        {
            m_pixelFormat = reader.readUInt8();
            m_stride = reader.readUInt16();
            m_width = reader.readUInt16();
            m_height = reader.readUInt16();
            m_offsetX = reader.readUInt16();
            m_offsetY = reader.readUInt16();
            m_name = reader.readString();
        }


        TextureDataChunk::TextureDataChunk()
            : m_numPixels(0)
            , m_BPP(0)
            , m_data()
        {
        }

        void TextureDataChunk::read(EndianStreamReader& reader)
        {
            m_numPixels = reader.readUInt32();
            m_BPP = reader.readUInt32();
            m_data.resize(m_BPP * m_numPixels);
            reader.read(&m_data[0], m_numPixels * m_BPP);
        }

        ModelHeadChunk::ModelHeadChunk()
            : m_unkonwn(0)
            , m_name()
        {
        }

        void ModelHeadChunk::read(EndianStreamReader& reader)
        {
            m_unkonwn = reader.readUInt16();
            m_name = reader.readString();
        }

        ModelVerticesChunk::ModelVerticesChunk()            
            : m_vertices()
        {
        }

        void ModelVerticesChunk::read(EndianStreamReader& reader)
        {
            uint32_t vertexCount = reader.readUInt32();
            m_vertices.resize(vertexCount);
            for (uint32_t i = 0; i < vertexCount; ++i)
            {
                Vertex3f& vertex = m_vertices[i];
                vertex.m_v[0] = reader.readFloat();
                vertex.m_v[1] = reader.readFloat();
                vertex.m_v[2] = reader.readFloat();
            }
        }

        ModelUVsChunk::ModelUVsChunk()
            : m_uv()
        {
        }

        void ModelUVsChunk::read(EndianStreamReader& reader)
        {
            uint32_t uvCount = reader.readUInt32();
            m_uv.resize(uvCount);
            for (uint32_t i = 0; i < uvCount; ++i)
            {
                Vertex2f& uv = m_uv[i];
                uv.m_v[0] = reader.readFloat();
                uv.m_v[1] = reader.readFloat();
            }
        }

        ModelFacesChunk::ModelFacesChunk()
            : m_faces()
        {
        }

        void ModelFacesChunk::read(EndianStreamReader& reader)
        {
            uint32_t facesCount = reader.readUInt32();
            m_faces.resize(facesCount);
            for (uint32_t i = 0; i < facesCount; ++i)
            {
                Face& face = m_faces[i];
                face.m_v[0] = reader.readUInt16();
                face.m_v[1] = reader.readUInt16();
                face.m_v[2] = reader.readUInt16();

                face.m_unknown[0] = reader.readUInt8();
                face.m_unknown[1] = reader.readUInt8();
                face.m_unknown[2] = reader.readUInt8();
            }
        }

        ModelMaterialsChunk::ModelMaterialsChunk()
            : m_materials()
        {
        }

        void ModelMaterialsChunk::read(EndianStreamReader& reader)
        {
            uint32_t materialsCount = reader.readUInt32();
            m_materials.reserve(materialsCount);
            for (uint32_t i = 0; i < materialsCount; ++i)
            {
                m_materials.push_back(reader.readString());                
            }
        }

        ModelFaceMaterialsChunk::ModelFaceMaterialsChunk()
            : m_faceMats()
        {
        }

        void ModelFaceMaterialsChunk::read(EndianStreamReader& reader)
        {
            uint32_t faceMatCount = reader.readUInt32();
            uint32_t bytesPerEntry = reader.readUInt32();
            if (bytesPerEntry != 2)
                throw Commons::SerializationException("Face material indexes is not 16 bit");

            m_faceMats.reserve(faceMatCount);
            for (uint32_t i = 0; i < faceMatCount; ++i)
            {
                m_faceMats.push_back(reader.readUInt16());
            }
        }

        MaterialAttributesV1Chunk::MaterialAttributesV1Chunk()
            : m_color(0)
            , m_otherColors()
            , m_flags(0)
            , m_transform()
            , m_indexBase(0)
            , m_indexRange(0)
            , m_name()
        {
        }

        void MaterialAttributesV1Chunk::read(EndianStreamReader& reader)
        {
            m_color = reader.readUInt32();
            for (int i = 0; i < 4; ++i)
                m_otherColors[i] = reader.readUInt32();
            m_flags = reader.readUInt16();
            for (int i = 0; i < 6; ++i)
                m_transform[i] = reader.readFloat();
            m_indexBase = reader.readUInt8();
            m_indexRange = reader.readUInt8();
            m_name = reader.readString();
        }

        MaterialAttributesV2Chunk::MaterialAttributesV2Chunk()
            : m_color(0)
            , m_otherColors()
            , m_flags(0)
            , m_transform() // TODO
            , m_unk(0)
            , m_unk2()
            , m_name()
        {
        }

        void MaterialAttributesV2Chunk::read(EndianStreamReader& reader)
        {
            m_color = reader.readUInt32();
            for (int i = 0; i < 4; ++i)
                m_otherColors[i] = reader.readUInt32();
            m_flags = reader.readUInt32();
            for (int i = 0; i < 6; ++i)
                m_transform[i] = reader.readFloat();
            m_unk = reader.readUInt32();
            reader.read(m_unk2, 13);
            m_name = reader.readString();
        }

        MaterialPixmapNameChunk::MaterialPixmapNameChunk()
            : m_name()
        {
        }

        void MaterialPixmapNameChunk::read(EndianStreamReader& reader)
        {
            m_name = reader.readString();
        }

        MaterialShadetabNameChunk::MaterialShadetabNameChunk()
            : m_name()
        {
        }

        void MaterialShadetabNameChunk::read(EndianStreamReader& reader)
        {
            m_name = reader.readString();
        }

        ActorNameChunk::ActorNameChunk()
            : m_flags(0)
            , m_name()
        {
        }
        
        void ActorNameChunk::read(EndianStreamReader& reader)
        {
            m_flags = reader.readUInt16();
            m_name = reader.readString();
        }

        ActorMatrixChunk::ActorMatrixChunk()
            : m_matrix() // TODO
        {
            m_matrix[15] = 1.F;
        }

        void ActorMatrixChunk::read(EndianStreamReader& reader)
        {
            for (int i = 0; i < 12; ++i)
                m_matrix[i] = reader.readFloat();
            // TODO
            m_matrix[15] = 1.F;
        }

        ActorPushChunk::ActorPushChunk()
        {
        }

        void ActorPushChunk::read(EndianStreamReader& reader)
        {
        }
        
        ActorPopChunk::ActorPopChunk()
        {
        }

        void ActorPopChunk::read(EndianStreamReader& reader)
        {
        }
     
        
        ActorModelChunk::ActorModelChunk()
            : m_name()
        {
        }

        void ActorModelChunk::read(EndianStreamReader& reader)
        {
            m_name = reader.readString();
        }

        ActorEmptyChunk::ActorEmptyChunk()
        {
        }

        void ActorEmptyChunk::read(EndianStreamReader& reader)
        {
        }
                        
        ActorMaterialChunk::ActorMaterialChunk()
            : m_name()
        {
        }

        void ActorMaterialChunk::read(EndianStreamReader& reader)
        {
            m_name = reader.readString();
        }
        
        ActorBBoxChunk::ActorBBoxChunk()
            : m_pos()
            , m_size()
        {
            // TODO
        }

        void ActorBBoxChunk::read(EndianStreamReader& reader)
        {
            for (uint32_t i = 0; i < 3; ++i)
                m_pos[i] = reader.readFloat();
            for (uint32_t i = 0; i < 3; ++i)
                m_size[i] = reader.readFloat();
        }
    }
}
