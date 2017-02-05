#include <Serialization/ChunkWriter.h>
#include <Streams/StreamWriter.h>
#include <Serialization/ChunkHeader.h>
#include <Exception/Exception.h>
#include <Common/StringUtils.h>
#include <cassert>

using namespace Commons;

namespace OpenCarma
{
    namespace BRender
    {
        ChunkWriter::ChunkWriter(const Commons::IOStreamPtr& stream, const FileHeader& fileheader)
            : mWriter(stream, Endianness::BIG_ENDIAN)
            , mCurHeaderOffset(0)
            , mCurDataOffset(0)
            , mCurHeader()
        {
            assert(stream);

            beginChunk(ChunkHeader::CHUNK_FILE_HEADER);
            fileheader.write(mWriter);
            endChunk();
        }

        void ChunkWriter::beginChunk(uint32_t magic)
        {
            assert(mCurDataOffset == 0);
            mCurHeaderOffset = mWriter.tell();
            mCurHeader.setMagic(magic);
            mCurHeader.setSize(0);
            mCurHeader.write(mWriter);
            mCurDataOffset = mWriter.tell();
        }

        void ChunkWriter::endChunk()
        {
            assert(mCurDataOffset != 0);
            IOStream::size_type lastPos = mWriter.tell();
            mWriter.seek(mCurHeaderOffset, IOStream::ORIGIN_SET);
            mCurHeader.setSize(lastPos - mCurDataOffset);
            mCurHeader.write(mWriter);
            mWriter.seek(lastPos, IOStream::ORIGIN_SET);
            mCurDataOffset = 0;
            mCurHeaderOffset = 0;
        }

        void ChunkWriter::writeNullChunk()
        {
            ChunkHeader::NULL_CHUNK.write(mWriter);
        }

        void ChunkWriter::finish()
        {
            mWriter.flush();
        }
    }
}
