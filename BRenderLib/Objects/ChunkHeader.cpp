#include <Objects/ChunkHeader.h>
#include <BigEndianStreamReader.h>
#include <Exception.h>


namespace OpenCarma
{
    namespace BRender
    {
        ChunkHeader::ChunkHeader() :
            m_magic(0),
            m_size(0)
        {
        }

        void ChunkHeader::read(BigEndianStreamReader& reader)
        {
            m_magic = reader.readUInt32();
            m_size = reader.readUInt32();
            // TODO: type the chunk magic, size & offset here...
        }


        FileHeaderChunk::FileHeaderChunk()
            : m_version1(0)
            , m_version2(0)
        {
        }

        void FileHeaderChunk::read(BigEndianStreamReader& reader)
        {
            m_version1 = reader.readUInt32();
            m_version2 = reader.readUInt32();
        }

        TextureHeadChunk::TextureHeadChunk()
            : m_type(0)
            , m_width1(0)
            , m_width2(0)
            , m_height(0)
            , m_u1(0)
            , m_u2(0)
            , m_name()
        {
        }

        void TextureHeadChunk::read(BigEndianStreamReader& reader)
        {
            m_type = reader.readUInt8();
            m_width1 = reader.readUInt16();
            m_width2 = reader.readUInt16();
            m_height = reader.readUInt16();
            m_u1 = reader.readUInt16();
            m_u2 = reader.readUInt16();
            m_name = reader.readString();
        }


        TextureDataChunk::TextureDataChunk()
            : m_numData(0)
            , m_sizeData(0)
            , m_data()
        {
        }

        void TextureDataChunk::read(BigEndianStreamReader& reader)
        {
            m_numData = reader.readUInt32();
            m_sizeData = reader.readUInt32();
            m_data.resize(m_numData * m_sizeData);
            reader.read(&m_data[0], m_numData * m_sizeData);
        }

        ModelHeadChunk::ModelHeadChunk()
            : m_unkonwn(0)
            , m_name()
        {
        }

        void ModelHeadChunk::read(BigEndianStreamReader& reader)
        {
            m_unkonwn = reader.readUInt16();
            m_name = reader.readString();
        }

        ModelVerticesChunk::ModelVerticesChunk()            
            : m_vertices()
        {
        }

        void ModelVerticesChunk::read(BigEndianStreamReader& reader)
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

        void ModelUVsChunk::read(BigEndianStreamReader& reader)
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

        void ModelFacesChunk::read(BigEndianStreamReader& reader)
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

        void ModelMaterialsChunk::read(BigEndianStreamReader& reader)
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

        void ModelFaceMaterialsChunk::read(BigEndianStreamReader& reader)
        {
            uint32_t faceMatCount = reader.readUInt32();
            uint32_t bytesPerEntry = reader.readUInt32();
            if (bytesPerEntry != 2)
                throw SerializationException("Face material indexes is not 16 bit");

            m_faceMats.reserve(faceMatCount);
            for (uint32_t i = 0; i < faceMatCount; ++i)
            {
                m_faceMats.push_back(reader.readUInt16());
            }
        }

        




        //    MaterialAttributesV1Chunk::MaterialAttributesV1Chunk()
        //        : m_color(0)
        //        , m_otherColors()
        //        , m_flags(0)
        //        , m_transform()
        //        , m_simpleMatPixelIndex(0)
        //        , m_simpleMatGradientCount(0)
        //        , m_name()
        //    {
        //    }

        //    void MaterialAttributesV1Chunk::ReadFromStream(const ChunkHeader& header, BigEndianStreamReader& stream)
        //    {
        //        setMagic(header.getMagic());
        //        setSize(header.getSize());

        //        m_color = stream.readUInt32();
        //        for (int i = 0; i < 4; ++i)
        //            m_otherColors[i] = stream.readUInt32();
        //        m_flags = stream.readUInt16();
        //        for (int i = 0; i < 6; ++i)
        //            m_transform[i] = stream.readFloat();
        //        m_simpleMatPixelIndex = stream.readUInt8();
        //        m_simpleMatGradientCount = stream.readUInt8();
        //        m_name = stream.readString();
        //    }

        //    ActorStartChunk::ActorStartChunk()
        //        : m_flags(0)
        //        , m_name()
        //    {
        //    }

        //    void ActorStartChunk::ReadFromStream(const ChunkHeader& header, BigEndianStreamReader& stream)
        //    {
        //        setMagic(header.getMagic());
        //        setSize(header.getSize());

        //        m_flags = stream.readUInt16();
        //        m_name = stream.readString();
        //    }

        //    TransformMatrixChunk::TransformMatrixChunk()
        //        : m_matrix()
        //    {
        //        m_matrix[15] = 1.F;
        //    }

        //    void TransformMatrixChunk::ReadFromStream(const ChunkHeader& header, BigEndianStreamReader& stream)
        //    {
        //        setMagic(header.getMagic());
        //        setSize(header.getSize());

        //        for (int i = 0; i < 12; ++i)
        //            m_matrix[i] = stream.readFloat();
        //        // TODO
        //        m_matrix[15] = 1.F;
        //    }
        //    
        //    HierarchyBeginChunk::HierarchyBeginChunk()
        //    {
        //    }

        //    void HierarchyBeginChunk::ReadFromStream(const ChunkHeader& header, BigEndianStreamReader& stream)
        //    {
        //        setMagic(header.getMagic());
        //        setSize(header.getSize());
        //    }

        //    HierarchyEndChunk::HierarchyEndChunk()
        //    {
        //    }

        //    void HierarchyEndChunk::ReadFromStream(const ChunkHeader& header, BigEndianStreamReader& stream)
        //    {
        //        setMagic(header.getMagic());
        //        setSize(header.getSize());
        //    }

        //    BBoxChunk::BBoxChunk()
        //    {
        //        // TODO: zero
        //    }

        //    void BBoxChunk::ReadFromStream(const ChunkHeader& header, BigEndianStreamReader& stream)
        //    {
        //        setMagic(header.getMagic());
        //        setSize(header.getSize());

        //        for (uint32_t i = 0; i < 3; ++i)
        //            m_pos[i] = stream.readFloat();
        //        for (uint32_t i = 0; i < 3; ++i)
        //            m_size[i] = stream.readFloat();
        //    }
        //    
        //    MaterialNamesChunk::MaterialNamesChunk()
        //        : m_name()
        //    {
        //    }

        //    void MaterialNamesChunk::ReadFromStream(const ChunkHeader& header, BigEndianStreamReader& stream)
        //    {
        //        setMagic(header.getMagic());
        //        setSize(header.getSize());

        //        m_name = stream.readString();
        //    }
    }
}
