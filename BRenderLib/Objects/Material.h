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
//
//material = [
//    identifier = "charles";
//    colour = [173, 173, 173];
//    ambient = 0.15;
//    diffuse = 0.35;
//    specular = 0.15;
//    power = 10;
//    flags = [always_visible, two_sided, light, smooth, perspective];
//    colour_map = "charles.pix";
//    index_base = 0;
//    index_range = 168;
//    index_shade = "charles.tab";
//    map_transform = [[1.0, 0], [0, 1.0], [0.0, 0.0]];
//];