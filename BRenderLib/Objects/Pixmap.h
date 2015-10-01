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
                PF_PAL8 = 3,
                PF_RGB555_BE = 4,
                PF_RGB565_BE = 5,
                PF_RGB24 = 6,
                PF_XRGB = 7,
                PF_ARGB = 8,
                PF_Y400A = 18,
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

            inline uint8_t Pixmap::getColorPAL8(uint32_t index) const
            {
                return m_data.m_data[index];
            }

            inline uint32_t Pixmap::getColorARGB(uint32_t index) const
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
