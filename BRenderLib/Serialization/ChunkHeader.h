#pragma once
#include <Common.h>

namespace Commons
{
    class StreamReader;
    class StreamWriter;
}

namespace OpenCarma
{
    namespace BRender
    {
        class BR_API ChunkHeader
        {
        public:
            static const uint32_t CHUNK_NULL = 0x0;
            static const uint32_t CHUNK_FILE_HEADER = 0x12;
            static const uint32_t CHUNK_TEXTURE_HEAD = 0x3;
            static const uint32_t CHUNK_TEXTURE_DATA = 0x21;
            static const uint32_t CHUNK_MATERIAL_ATTRIBUTES_V1 = 0x4;
            static const uint32_t CHUNK_MATERIAL_ATTRIBUTES_V2 = 0x3C;
            static const uint32_t CHUNK_MATERIAL_PIXELMAP_NAME = 0x1C;
            static const uint32_t CHUNK_MATERIAL_SHADETAB_NAME = 0x1F;
            static const uint32_t CHUNK_MODEL_HEAD = 0x36;
            static const uint32_t CHUNK_MODEL_VERTICES = 0x17;
            static const uint32_t CHUNK_MODEL_UVS = 0x18;
            static const uint32_t CHUNK_MODEL_FACES = 0x35;
            static const uint32_t CHUNK_MODEL_MATERIALS = 0x16;
            static const uint32_t CHUNK_MODEL_FACE_MATERIALS = 0x1A;
            static const uint32_t CHUNK_ACTOR_NAME = 0x23;
            static const uint32_t CHUNK_ACTOR_MODEL_NAME = 0x24;
            static const uint32_t CHUNK_ACTOR_UNKNOWN = 0x25;
            static const uint32_t CHUNK_ACTOR_MATERIAL_NAMES = 0x26;
            static const uint32_t CHUNK_ACTOR_HIERARCHY_BEGIN = 0x29;
            static const uint32_t CHUNK_ACTOR_HIERARCHY_END = 0x2A;
            static const uint32_t CHUNK_ACTOR_TRANSFORM_MATRIX = 0x2B;
            static const uint32_t CHUNK_ACTOR_BOUNDING_BOX = 0x32;

            static const ChunkHeader NULL_CHUNK;
        public:
            ChunkHeader();
            ChunkHeader(uint32_t magic, uint32_t size);

            uint32_t getMagic() const { return mMagic; }
            void setMagic(uint32_t magic) { mMagic = magic; }

            uint32_t getSize() const { return mSize; }
            void setSize(uint32_t size) { mSize = size; }

            bool operator==(const ChunkHeader& other) const { return mMagic == other.mMagic && mSize == other.mSize; }

        public:
            void read(Commons::StreamReader& reader);
            void write(Commons::StreamWriter& writer) const;

        private:
            uint32_t mMagic;
            uint32_t mSize;
        };

        class BR_API FileHeader
        {
        public:
            static const uint32_t VERSION_MAJOR = 2;
            static const uint32_t VERSION_MINOR = 2;

        public:
            FileHeader();
            FileHeader(uint32_t version1, uint32_t version2);

            void read(Commons::StreamReader& reader);
            void write(Commons::StreamWriter& writer) const;

            uint32_t getVersion1() const { return mVersion1; }
            uint32_t getVersion2() const { return mVersion2; }

        private:
            uint32_t mVersion1;
            uint32_t mVersion2;
        };     
    }
}
