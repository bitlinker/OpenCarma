#include <Objects/Palette.h>
#include <cassert>

namespace OpenCarma
{
    namespace BRender
    {
        Palette::Palette()
            : m_header()
            , m_data()
        {
        }

        void Palette::fillHeader()
        {
            m_header.m_type = TextureHeadChunk::TYPE_PALETTE;
            m_header.m_width1 = m_data.m_sizeData; // RGBA
            m_header.m_width2 = 1; // Bits per index???
            m_header.m_height = m_data.m_numData; // Number of colors
            m_header.m_u1 = 0;   // ???
            m_header.m_u2 = 128; // ???
            m_header.m_name = "UNNAMED.PAL";
        }
        
        uint32_t Palette::getColor(uint8_t index) const
        {
            const uint32_t* src = reinterpret_cast<const uint32_t*>(&m_data.m_data[0]);
            uint32_t clr = src[index];
            if (index > 0)
                clr = clr | 0xFF;
            return clr;
        }

        bool Palette::isValid() const
        {
            if (m_header.m_type != TextureHeadChunk::TYPE_PALETTE)
                return false;

            if (m_header.m_width1 != 4 || m_data.m_sizeData != 4)
                return false;

            if (m_header.m_width2 != 1)
                return false;

            if (m_data.m_numData != 256)
                return false;

            if (m_data.m_data.size() != m_data.m_numData * m_data.m_sizeData)
                return false;

            return true;
        }
    }
}