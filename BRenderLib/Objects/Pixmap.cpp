#include "Pixmap.h"

namespace OpenCarma
{
	namespace BRender
	{
		Pixmap::Pixmap()
            : m_header()
            , m_data()
		{
		}

        bool Pixmap::isValid() const
        {
            if (m_header.m_type != TextureHeadChunk::TYPE_PIXELMAP)
                return false;

            if (!m_header.m_width1 || !m_header.m_height)
                return false;

            if (m_header.m_width1 != m_header.m_width2)
                return false;

            if (m_header.m_width1 * m_header.m_height * m_data.m_sizeData != m_data.m_numData)
                return false;

            if (m_data.m_sizeData != 1)
                return false;

            if (m_data.m_data.size() != m_data.m_numData * m_data.m_sizeData)
                return false;

            return true;
        }
	}
}
