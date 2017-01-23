#pragma once

#include <Common.h>
#include <Streams/IOStream.h>

#include <Objects/Pixmap.h>

namespace OpenCarma
{
    namespace BRender
    {
		class BR_API PixmapSerializer : protected ChunkReaderListener
        {
        private:
            PixmapSerializer() {};
            virtual ~PixmapSerializer() {};

        public:
            const std::vector<PixmapPtr>& deserialize(const Commons::IOStreamPtr& stream);
            void serialize(const PixmapPtr& pal, const Commons::IOStreamPtr& stream);

		protected:
			virtual bool onChunk(const ChunkHeader& header, StreamReader& reader);

		private:
			PixmapPtr mCurPixmap;
			std::vector<PixmapPtr> mPixelmaps;
        };
    }
}
