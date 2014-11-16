#pragma once
#include <Common.h>
#include <Objects/ChunkHeader.h>

namespace OpenCarma
{
	namespace BRender
	{
		// BRender palette
		class BR_API Palette
		{
            friend class PaletteSerializer;
		public:
			Palette();

            const string& getName() const { return m_header.m_name; }
            uint32_t getNumColors() const { return m_header.m_height; }
            uint32_t getColor(uint8_t index) const;
            bool isValid() const;

        private:
            void fillHeader();

		private:
            TextureHeadChunk m_header;
            TextureDataChunk m_data;
		};

        typedef std::shared_ptr<Palette> PalettePtr;
	}
}