#pragma once
#include <Common.h>
#include <Serialization/ChunkHeader.h>
#include <Streams/IOStream.h>

namespace OpenCarma
{
	namespace BRender
	{
		class BR_API ChunkReader
		{
        protected:
            ChunkReader() {};
            virtual ~ChunkReader() {};

            virtual void onStart(const FileHeader& fileHeader) {};
            virtual bool onChunkRead(const ChunkHeader& header, Commons::StreamReader& reader) = 0;
            virtual void onFinish() {};

			void doRead(const Commons::IOStreamPtr& stream);
		};
	}
}