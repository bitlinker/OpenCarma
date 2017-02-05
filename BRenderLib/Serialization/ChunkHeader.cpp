#include <Serialization/ChunkHeader.h>
#include <Objects/Pixmap.h>
#include <Streams/StreamReader.h>
#include <Streams/StreamWriter.h>
#include <Exception/Exception.h>


namespace OpenCarma
{
    namespace BRender
    {
        const ChunkHeader ChunkHeader::NULL_CHUNK;

        ChunkHeader::ChunkHeader()
            : mMagic(0)
            , mSize(0)
        {
        }

        ChunkHeader::ChunkHeader(uint32_t magic, uint32_t size)
            : mMagic(magic)
            , mSize(size)
        {
        }

        void ChunkHeader::read(Commons::StreamReader& reader)
        {
            mMagic = reader.readUInt32();
            mSize = reader.readUInt32();
        }

        void ChunkHeader::write(Commons::StreamWriter& writer) const
        {
            writer.writeUInt32(mMagic);
            writer.writeUInt32(mSize);
        }

        FileHeader::FileHeader()
            : mVersion1(VERSION_MAJOR)
            , mVersion2(VERSION_MINOR)
        {
        }

        FileHeader::FileHeader(uint32_t version1, uint32_t version2)
            : mVersion1(version1)
            , mVersion2(version2)
        {
        }

        void FileHeader::read(Commons::StreamReader& reader)
        {
            mVersion1 = reader.readUInt32();
            mVersion2 = reader.readUInt32();
        }

        void FileHeader::write(Commons::StreamWriter& writer) const
        {
            writer.writeUInt32(mVersion1);
            writer.writeUInt32(mVersion2);
        }
    }
}
