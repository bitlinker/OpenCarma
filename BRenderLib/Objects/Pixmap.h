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
            enum PixelFormat 
            {
                /*
                * Each pixel is an index into a colour map
                */
                BR_PMT_INDEX_1,
                BR_PMT_INDEX_2,
                BR_PMT_INDEX_4,
                BR_PMT_INDEX_8,

                /*
                * True colour RGB
                */
                BR_PMT_RGB_555,		/* 16 bits per pixel */
                BR_PMT_RGB_565,		/* 16 bits per pixel */
                BR_PMT_RGB_888,		/* 24 bits per pixel */
                BR_PMT_RGBX_888,	/* 32 bits per pixel */
                BR_PMT_RGBA_8888,	/* 32 bits per pixel */

                                    /*
                                    * YUV
                                    */
                BR_PMT_YUYV_8888,	/* YU YV YU YV ... */
                BR_PMT_YUV_888,

                /*
                * Depth
                */
                BR_PMT_DEPTH_16,
                BR_PMT_DEPTH_32,

                /*
                * Opacity
                */
                BR_PMT_ALPHA_8,

                /*
                * Opacity + Index
                */
                BR_PMT_INDEXA_88
            };

        public:
            // Creates an empty pixel map
            Pixmap();

            PixelFormat getPixelFormat() { return static_cast<PixelFormat>(m_header.m_pixelFormat); }
            uint32_t getStride() const { return m_header.m_stride; }
            uint32_t getWidth() const { return m_header.m_width; }
            uint32_t getHeight() const { return m_header.m_height; }
            uint32_t getXOffset() const { return m_header.m_offsetX; }
            uint32_t getYOffset() const { return m_header.m_offsetY; }
            uint32_t getBPP() const { return m_data.m_BPP; }
            uint32_t getNumPixels() const { return m_data.m_numPixels; }
            const std::string& getName() const { return m_header.m_name; }
            bool isValid() const;

            inline const std::vector<uint8_t>& getPixels() const
            {
                return m_data.m_data;
            }

            inline uint8_t getColorPAL8(uint32_t index) const
            {
                return m_data.m_data[index];
            }

            inline uint32_t getColorARGB(uint32_t index) const
            {
                return reinterpret_cast<const uint32_t*>(&m_data.m_data[0])[index];
            }

        private:
            TextureHeadChunk m_header;
            TextureDataChunk m_data;
        };

        typedef std::shared_ptr<Pixmap> PixmapPtr;
    }
}
