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
            //static const uint16_t FLAG_DOUBLESIDED = 0x10;
            //static const uint16_t FLAG_ALWAYS_VISIBLE = 0x0; // TODO: update constants
            //static const uint16_t FLAG_LIGHT = 0x0; // TODO: update constants
            //static const uint16_t FLAG_SMOOTH = 0x0; // TODO: update constants
            //static const uint16_t FLAG_PERSPECTIVE = 0x0; // TODO: update constants
            //static const uint16_t FLAG_PRELIT = 0x0; // TODO: update constants
            //static const uint16_t FLAG_ENVIRONMENT = 0x0; // TODO: update constants
            //static const uint16_t FLAG_ENVIRONMENT_LOCAL = 0x0; // TODO: update constants
            //static const uint16_t FLAG_DECAL = 0x0; // TODO: update constants
            //static const uint16_t FLAG_FORCE_Z0 = 0x0; // TODO: update constants

            /*
            * Bits for br_material->flags
            */
            enum {
                BR_MATF_LIGHT = 0x00000001,
                BR_MATF_PRELIT = 0x00000002,

                BR_MATF_SMOOTH = 0x00000004,

                BR_MATF_ENVIRONMENT_I = 0x00000008,
                BR_MATF_ENVIRONMENT_L = 0x00000010,
                BR_MATF_PERSPECTIVE = 0x00000020,
                BR_MATF_DECAL = 0x00000040,

                BR_MATF_I_FROM_U = 0x00000080,
                BR_MATF_I_FROM_V = 0x00000100,
                BR_MATF_U_FROM_I = 0x00000200,
                BR_MATF_V_FROM_I = 0x00000400,

                BR_MATF_ALWAYS_VISIBLE = 0x00000800,
                BR_MATF_TWO_SIDED = 0x00001000,

                BR_MATF_FORCE_Z_0 = 0x00002000,

                BR_MATF_DITHER = 0x00004000
            };


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