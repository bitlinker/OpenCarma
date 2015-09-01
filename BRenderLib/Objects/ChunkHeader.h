#pragma once
#include "Common.h"


// All chunks should be packed
//#pragma pack(push, 1)

namespace OpenCarma
{
    namespace BRender
    {
        //! Chunk magics:
        // TODO: common list
        /*const uint32_t CHUNK_NULL = 0x0;
        const uint32_t CHUNK_HEADER = 0x12;
        const uint32_t CHUNK_TEXTURE_HEAD = 0x3;
        const uint32_t CHUNK_MATERIAL_ATTRIBUTES_V1 = 0x4;
        const uint32_t CHUNK_MATERIAL_ATTRIBUTES_V2 = 0x3C;
        const uint32_t CHUNK_TEXTURE_DATA = 0x21;
        const uint32_t CHUNK_PIXELMAP_NAME = 0x1C;
        const uint32_t CHUNK_SHADETAB_NAME = 0x1F;
        const uint32_t CHUNK_ACTOR_NAME = 0x23;
        const uint32_t CHUNK_ACTOR_MODEL_NAME = 0x24;
        const uint32_t CHUNK_ACTOR_UNKNOWN = 0x25;
        const uint32_t CHUNK_ACTOR_MATERIAL_NAMES = 0x26;
        const uint32_t CHUNK_ACTOR_HIERARCHY_BEGIN = 0x29;
        const uint32_t CHUNK_ACTOR_HIERARCHY_END = 0x2A;
        const uint32_t CHUNK_ACTOR_TRANSFORM_MATRIX = 0x2B;
        const uint32_t CHUNK_ACTOR_BOUNDING_BOX = 0x32;*/

        class BR_API Vertex3f
        {
        public:
            float m_v[3];
        };

        class BR_API Vertex2f
        {
        public:
            float m_v[2];
        };

        class BR_API Face
        {
        public:
            uint16_t m_v[3];
            uint8_t m_unknown[3];
        };

        class BigEndianStreamReader;

        class BR_API ChunkHeader
        {
        public:
            ChunkHeader();

            const uint32_t getMagic() const { return m_magic; }
            void setMagic(const uint32_t magic) { m_magic = magic; }

            const uint32_t getSize() const { return m_size; }
            void setSize(const uint32_t size) { m_size = size; }

            const bool isNULL() const { return (m_size == 0 && m_magic == 0); }

        public:
            // Returns false on eof
            void read(BigEndianStreamReader& reader);

        private:
            uint32_t m_magic;
            uint32_t m_size;
        };

        class BR_API ChunkBase
        {
        public:
            static const uint32_t MAGIC;
        };

        //! File header
        class BR_API FileHeaderChunk : public ChunkBase
        {
        public:
            static const uint32_t MAGIC = 0x12;

        public:
            FileHeaderChunk();

            void read(BigEndianStreamReader& reader);

        public:
            uint32_t m_version1;
            uint32_t m_version2;
        };

        //! Texture or palette or shadetab header chunk
        class BR_API TextureHeadChunk : public ChunkBase
        {
        public:
            static const uint32_t MAGIC = 0x3;

        public:
            TextureHeadChunk();
            void read(BigEndianStreamReader& reader);

        public:
            uint8_t m_pixelFormat;      //!< Pixel format
            uint16_t m_stride;	        //!< Stride
            uint16_t m_width;	        //!< Width
            uint16_t m_height;	        //!< Height
            uint16_t m_offsetX;         //!< oX
            uint16_t m_offsetY;         //!< oY
            string m_name;              //!< Null-terminated name
        };

        //! Texture data
        class BR_API TextureDataChunk : public ChunkBase
        {
        public:
            static const uint32_t MAGIC = 0x21;

        public:
            TextureDataChunk();

            void read(BigEndianStreamReader& reader);

        public:
            uint32_t m_numPixels;
            uint32_t m_BPP;
            std::vector<uint8_t> m_data;
        };

        //! Model name
        class BR_API ModelHeadChunk : public ChunkBase
        {
        public:
            static const uint32_t MAGIC = 0x36;

        public:
            ModelHeadChunk();

            void read(BigEndianStreamReader& reader);

        public:
            uint16_t m_unkonwn;
            std::string m_name;
        };

        class BR_API ModelVerticesChunk : public ChunkBase
        {
        public:
            static const uint32_t MAGIC = 0x17;

        public:
            ModelVerticesChunk();

            void read(BigEndianStreamReader& reader);

        public:
            std::vector<Vertex3f> m_vertices;
        };

        class BR_API ModelUVsChunk : public ChunkBase
        {
        public:
            static const uint32_t MAGIC = 0x18;

        public:
            ModelUVsChunk();

            void read(BigEndianStreamReader& reader);

        public:
            std::vector<Vertex2f> m_uv;
        };

        class BR_API ModelFacesChunk : public ChunkBase
        {
        public:
            static const uint32_t MAGIC = 0x35;

        public:
            ModelFacesChunk();

            void read(BigEndianStreamReader& reader);

        public:
            std::vector<Face> m_faces;
        };

        class BR_API ModelMaterialsChunk : public ChunkBase
        {
        public:
            static const uint32_t MAGIC = 0x16;

        public:
            ModelMaterialsChunk();

            void read(BigEndianStreamReader& reader);

        public:
            std::vector<string> m_materials;
        };

        class BR_API ModelFaceMaterialsChunk : public ChunkBase
        {
        public:
            static const uint32_t MAGIC = 0x1A;

        public:
            ModelFaceMaterialsChunk();

            void read(BigEndianStreamReader& reader);

        public:
            std::vector<uint16_t> m_faceMats; // 1-based
        };

        //! Material attributes chunk version 1
        class BR_API MaterialAttributesV1Chunk : public ChunkBase
        {
        public:
            static const uint32_t MAGIC = 0x04;

            // Flags: always_visible, two_sided, light, smooth, perspective

        public:
            MaterialAttributesV1Chunk();
            void read(BigEndianStreamReader& reader);

        public:
            uint32_t m_color;		            //!< Color, RGBA
            uint32_t m_otherColors[4];	        //!< Other colors [Diffuse/Ambient/Specular/power???]
            uint16_t m_flags;	                //!< Flags
            float m_transform[6];	            //!< Transform matrix // TODO: use matrix type
            uint8_t m_indexBase;                //!< ???
            uint8_t m_indexRange;               //!< ???
            string m_name;                      //!< Null-terminated name
        };

        //! Material attributes chunk version 2
        class BR_API MaterialAttributesV2Chunk : public ChunkBase
        {
        public:
            static const uint32_t MAGIC = 0x3C;

        public:
            MaterialAttributesV2Chunk();
            void read(BigEndianStreamReader& reader);

        public:
            uint32_t m_color;		            //!< Color, RGBA
            uint32_t m_otherColors[4];	        //!< Other colors [Diffuse/Ambient/Specular/Emmission???]
            uint32_t m_flags;	                //!< Flags
            float m_transform[6];	            //!< Transform matrix // TODO: use matrix type
            uint32_t m_unk;                     //!< ???
            uint8_t m_unk2[13];                 //!< ???
            string m_name;                      //!< Null-terminated name
        };

        //! Material pixelmap name chunk
        class BR_API MaterialPixmapNameChunk: public ChunkBase
        {
        public:
            static const uint32_t MAGIC = 0x1C;

        public:
            MaterialPixmapNameChunk();
            void read(BigEndianStreamReader& reader);

        public:
            string m_name;                      //!< Null-terminated name
        };

        //! Material shadetab name chunk
        class BR_API MaterialShadetabNameChunk : public ChunkBase
        {
        public:
            static const uint32_t MAGIC = 0x1F;

        public:
            MaterialShadetabNameChunk();
            void read(BigEndianStreamReader& reader);

        public:
            string m_name;                      //!< Null-terminated name
        };
            
        
        //! Actor
        class BR_API ActorNameChunk : public ChunkBase
        {
        public:
            static const uint32_t MAGIC = 0x23;

        public:
            ActorNameChunk();
            void read(BigEndianStreamReader& reader);

        public:
            uint16_t m_flags;	                //!< Flags            
            string m_name;                      //!< Null-terminated name
        };
        
        class BR_API ActorMatrixChunk : public ChunkHeader
        {
        public:
            static const uint32_t MAGIC = 0x2B;

        public:
            ActorMatrixChunk();
            void read(BigEndianStreamReader& reader);

        public:
            float m_matrix[16];	                //!< Transform matrix
        };

        class BR_API ActorPushChunk : public ChunkHeader
        {
        public:
            static const uint32_t MAGIC = 0x29;

        public:
            ActorPushChunk();
            void read(BigEndianStreamReader& reader);        
        };

        class BR_API ActorPopChunk : public ChunkHeader
        {
        public:
            static const uint32_t MAGIC = 0x2A;

        public:
            ActorPopChunk();
            void read(BigEndianStreamReader& reader);
        };     

        class BR_API ActorModelChunk : public ChunkHeader
        {
        public:
            static const uint32_t MAGIC = 0x24;

        public:
            ActorModelChunk();
            void read(BigEndianStreamReader& reader);
        public:
            string m_name;
        };

        class BR_API ActorEmptyChunk : public ChunkHeader
        {
        public:
            static const uint32_t MAGIC = 0x25;

        public:
            ActorEmptyChunk();
            void read(BigEndianStreamReader& reader);
        };

        class BR_API ActorMaterialChunk : public ChunkHeader
        {
        public:
            static const uint32_t MAGIC = 0x26;

        public:
            ActorMaterialChunk();
            void read(BigEndianStreamReader& reader);
        public:
            string m_name;
        };

        class BR_API ActorBBoxChunk : public ChunkHeader
        {
        public:
            static const uint32_t MAGIC = 0x32;

        public:
            ActorBBoxChunk();
            void read(BigEndianStreamReader& reader);

        public:
            float m_pos[3];
            float m_size[3];
        };
    }
}

//#pragma pack(pop)