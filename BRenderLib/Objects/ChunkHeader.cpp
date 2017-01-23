#include <Objects/ChunkHeader.h>
#include <Streams/StreamReader.h>
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

        void ChunkHeader::read(Commons::StreamReader& reader)
        {
            m_magic = reader.readUInt32();
            m_size = reader.readUInt32();
            // TODO: type the chunk magic, size & offset here...
            //printf("Magic: %x(%d), len: %d at: %d\n", m_magic, m_magic, m_size, reader.tell());
        }

        TextureHeadChunk::TextureHeadChunk()
            : mPixelFormat(0)
            , mStride(0)
            , mWidth(0)
            , mHeight(0)
            , mOffsetX(0)
            , mOffsetY(0)
            , mName()
        {
        }

        void TextureHeadChunk::read(Commons::StreamReader& reader)
        {
            mPixelFormat = reader.readUInt8();
            mStride = reader.readUInt16();
            mWidth = reader.readUInt16();
            mHeight = reader.readUInt16();
            mOffsetX = reader.readUInt16();
            mOffsetY = reader.readUInt16();
            mName = reader.readNullTermString();
        }


        TextureDataChunk::TextureDataChunk()
            : mNumPixels(0)
            , mBpp(0)
            , mData()
        {
        }

        void TextureDataChunk::read(Commons::StreamReader& reader)
        {
            mNumPixels = reader.readUInt32();
            mBpp = reader.readUInt32();
            mData.resize(mBpp * mNumPixels);
            reader.read(&mData[0], mNumPixels * mBpp);
        }

        ModelHeadChunk::ModelHeadChunk()
            : m_unkonwn(0)
            , mName()
        {
        }

        void ModelHeadChunk::read(Commons::StreamReader& reader)
        {
            m_unkonwn = reader.readUInt16();
            mName = reader.readNullTermString();
        }

        ModelVerticesChunk::ModelVerticesChunk()            
            : m_vertices()
        {
        }

        void ModelVerticesChunk::read(Commons::StreamReader& reader)
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

        void ModelUVsChunk::read(Commons::StreamReader& reader)
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

        void ModelFacesChunk::read(Commons::StreamReader& reader)
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

        void ModelMaterialsChunk::read(Commons::StreamReader& reader)
        {
            uint32_t materialsCount = reader.readUInt32();
            m_materials.reserve(materialsCount);
            for (uint32_t i = 0; i < materialsCount; ++i)
            {
                m_materials.push_back(reader.readNullTermString());
            }
        }

        ModelFaceMaterialsChunk::ModelFaceMaterialsChunk()
            : m_faceMats()
        {
        }

        void ModelFaceMaterialsChunk::read(Commons::StreamReader& reader)
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
            , mName()
        {
        }

        void MaterialAttributesV1Chunk::read(Commons::StreamReader& reader)
        {
            m_color = reader.readUInt32();
            for (int i = 0; i < 4; ++i)
                m_otherColors[i] = reader.readUInt32();
            m_flags = reader.readUInt16();
            for (int i = 0; i < 6; ++i)
                m_transform[i] = reader.readFloat();
            m_indexBase = reader.readUInt8();
            m_indexRange = reader.readUInt8();
            mName = reader.readNullTermString();
        }

        MaterialAttributesV2Chunk::MaterialAttributesV2Chunk()
            : m_color(0)
            , m_otherColors()
            , m_flags(0)
            , m_transform() // TODO
            , m_unk(0)
            , m_unk2()
            , mName()
        {
        }

        void MaterialAttributesV2Chunk::read(Commons::StreamReader& reader)
        {
            m_color = reader.readUInt32();
            for (int i = 0; i < 4; ++i)
                m_otherColors[i] = reader.readUInt32();
            m_flags = reader.readUInt32();
            for (int i = 0; i < 6; ++i)
                m_transform[i] = reader.readFloat();
            m_unk = reader.readUInt32();
            reader.read(m_unk2, 13);
            mName = reader.readNullTermString();
        }

        MaterialPixmapNameChunk::MaterialPixmapNameChunk()
            : mName()
        {
        }

        void MaterialPixmapNameChunk::read(Commons::StreamReader& reader)
        {
            mName = reader.readNullTermString();
        }

        MaterialShadetabNameChunk::MaterialShadetabNameChunk()
            : mName()
        {
        }

        void MaterialShadetabNameChunk::read(Commons::StreamReader& reader)
        {
            mName = reader.readNullTermString();
        }

        ActorNameChunk::ActorNameChunk()
            : m_flags(0)
            , mName()
        {
        }
        
        void ActorNameChunk::read(Commons::StreamReader& reader)
        {
            m_flags = reader.readUInt16();
            mName = reader.readNullTermString();
        }

        ActorMatrixChunk::ActorMatrixChunk()
            : m_matrix() // TODO
        {
            m_matrix[15] = 1.F;
        }

        void ActorMatrixChunk::read(Commons::StreamReader& reader)
        {
            for (int i = 0; i < 12; ++i)
                m_matrix[i] = reader.readFloat();
            // TODO
            m_matrix[15] = 1.F;
        }

        ActorPushChunk::ActorPushChunk()
        {
        }

        void ActorPushChunk::read(Commons::StreamReader& reader)
        {
        }
        
        ActorPopChunk::ActorPopChunk()
        {
        }

        void ActorPopChunk::read(Commons::StreamReader& reader)
        {
        }
     
        
        ActorModelChunk::ActorModelChunk()
            : mName()
        {
        }

        void ActorModelChunk::read(Commons::StreamReader& reader)
        {
            mName = reader.readNullTermString();
        }

        ActorEmptyChunk::ActorEmptyChunk()
        {
        }

        void ActorEmptyChunk::read(Commons::StreamReader& reader)
        {
        }
                        
        ActorMaterialChunk::ActorMaterialChunk()
            : mName()
        {
        }

        void ActorMaterialChunk::read(Commons::StreamReader& reader)
        {
            mName = reader.readNullTermString();
        }
        
        ActorBBoxChunk::ActorBBoxChunk()
            : m_pos()
            , m_size()
        {
            // TODO
        }

        void ActorBBoxChunk::read(Commons::StreamReader& reader)
        {
            for (uint32_t i = 0; i < 3; ++i)
                m_pos[i] = reader.readFloat();
            for (uint32_t i = 0; i < 3; ++i)
                m_size[i] = reader.readFloat();
        }
    }
}
