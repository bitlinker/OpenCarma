#pragma once
#include <Common.h>
#include <Objects/ChunkHeader.h>

namespace OpenCarma
{
	namespace BRender
	{
        class BR_API Pixmap
		{
            friend class TextureSerializer;
		public:
            // Creates an empty pixel map
            Pixmap();

            const uint32_t getWidth() const { return m_header.m_width1; }
            const uint32_t getHeight() const { return m_header.m_height; }
            const string& getName() const { return m_header.m_name; }
            const std::vector<uint8_t>& getPixels() const { return m_data.m_data; }
            bool isValid() const;

		private:
            TextureHeadChunk m_header;
            TextureDataChunk m_data;
		};

        typedef std::shared_ptr<Pixmap> PixmapPtr;
	}
}
