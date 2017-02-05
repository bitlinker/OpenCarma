#pragma once
#include <Common.h>
#include <Serialization/ChunkReader.h>
#include <Streams/IOStream.h>
#include <Objects/Pixmap.h>
#include <functional>

namespace OpenCarma
{
    namespace BRender
    {
		class BR_API PixmapSerializer : protected  ChunkReader
        {
        public:
            typedef std::function<void(const PixmapPtr&)> TReadCallback;
            typedef std::function<const PixmapPtr()> TWriteCallback; // Return null to finish
            
        public:
            PixmapSerializer();
            virtual ~PixmapSerializer() {};

            void read(const Commons::IOStreamPtr& stream, TReadCallback callback);
            void write(const Commons::IOStreamPtr& stream, TWriteCallback callback);

		protected:
            virtual bool onChunkRead(const ChunkHeader& header, Commons::StreamReader& reader);

		private:
			PixmapPtr mCurPixmap;
            bool mHasHeaderChunk;
            bool mHasDataChunk;
            TReadCallback mReadCallback;
        };
    }
}
