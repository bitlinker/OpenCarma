#include "Pixmap.h"

namespace OpenCarma
{
	namespace BRender
	{
		Pixmap::Pixmap()
			: mPixelFormat(BR_PMT_INDEX_8)
			, mStride(0)
			, mWidth(0)
			, mHeight(0)
			, mOffsetX(0)
			, mOffsetY(0)
			, mName()
			, mNumPixels(0)
			, mBpp(1)
			, mData()
		{
		}

        bool Pixmap::isValid() const
        {
            // TODO: more complex checks
            // TODO: logging
            /*if (!m_header.m_pixelFormat)
                return false;

            if (!m_header.m_width || !m_header.m_height)
                return false;

            if (m_header.m_width * m_data.m_BPP != m_header.m_stride)
                return false;

            if (m_header.m_width * m_header.m_height != m_data.m_numPixels)
                return false;

            if (!m_data.m_numPixels || !m_data.m_BPP)
                return false;

            if (m_data.m_data.size() != m_data.m_numPixels * m_data.m_BPP)
                return false;*/

            return true;
        }

        // TODO: Pixmap utils
        /*const uint32_t* src = reinterpret_cast<const uint32_t*>(&m_data.m_data[0]);
        uint32_t clr = src[index];
        if (index > 0)
            clr = clr | 0xFF;
        return clr;*/
	}
}
