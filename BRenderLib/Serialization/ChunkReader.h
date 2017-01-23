#pragma once
#include <Common.h>
#include <Objects/ChunkHeader.h>
#include <Streams/StreamReader.h>

namespace OpenCarma
{
	namespace BRender
	{
		class BR_API ChunkReaderListener
		{
		public:
			virtual void onStart() {};
			virtual bool onChunkRead(const ChunkHeader& header, Commons::StreamReader& reader) = 0;
			virtual void onFinish() {};
			virtual ~ChunkReaderListener() {};
		};

		class BR_API ChunkReader
		{
		public:
			void deserialize(const Commons::IOStreamPtr& stream, ChunkReaderListener* listener);
		};
	}
}