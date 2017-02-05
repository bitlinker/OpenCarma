#pragma once
#include <Common.h>
#include <Serialization/ChunkHeader.h>
#include <Streams/IOStream.h>
#include <Streams/StreamWriter.h>

namespace OpenCarma
{
    namespace BRender
    {
        class BR_API ChunkWriter
        {
        public:
            ChunkWriter(const Commons::IOStreamPtr& stream, const FileHeader& fileheader);
            void beginChunk(uint32_t magic);
            void endChunk();
            void writeNullChunk();
            void finish();

            Commons::StreamWriter& getStreamWriter() { return mWriter; }
        private:
            Commons::StreamWriter mWriter;
            Commons::IOStream::size_type mCurHeaderOffset;
            Commons::IOStream::size_type mCurDataOffset;
            ChunkHeader mCurHeader;
        };
    }
}
