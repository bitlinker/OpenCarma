#pragma once
#include <Common.h>
#include <Objects/ChunkHeader.h>

namespace OpenCarma
{
	namespace BRender
	{
        class BR_API Material
		{
        public:
            static const uint16_t FLAG_DOUBLESIDED = 0x10;

		public:
			Material();

            bool isValid() const;

        public:
            MaterialAttributesV1Chunk m_header;
            // TODO: v2?
            MaterialPixmapNameChunk m_pixelmap;
            MaterialShadetabNameChunk m_shadetab;
		};

        typedef std::shared_ptr<Material> MaterialPtr;
	}
}
