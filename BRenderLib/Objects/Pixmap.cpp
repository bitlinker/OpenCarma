#include "Pixmap.h"

namespace OpenCarma
{
	namespace BRender
	{
		Pixmap::Pixmap(PixelFormat format, uint32_t width, uint32_t height, int32_t stride)
			: mPixelFormat(format)
			, mStride(stride)
			, mWidth(width)
			, mHeight(height)
			, mOffsetX(0)
			, mOffsetY(0)
			, mName()
			, mData(stride * height)
		{
		}

        uint32_t Pixmap::getBpp() const
        {
            switch (mPixelFormat)
            {
            case BR_PMT_INDEX_1:
            case BR_PMT_INDEX_2:
            case BR_PMT_INDEX_4:
            case BR_PMT_INDEX_8:
            case BR_PMT_ALPHA_8:
                return 1; // TODO: check
            case BR_PMT_RGB_555:
            case BR_PMT_RGB_565:
            case BR_PMT_DEPTH_16:
            case BR_PMT_INDEXA_88:
                return 2;
            case BR_PMT_RGB_888:
            case BR_PMT_YUV_888:
                return 3;
            case BR_PMT_RGBX_888:
            case BR_PMT_RGBA_8888:
            case BR_PMT_YUYV_8888:
            case BR_PMT_DEPTH_32:
                return 4;
            }
            return 0;
        }

      

        // TODO: Pixmap utils
        /*const uint32_t* src = reinterpret_cast<const uint32_t*>(&m_data.m_data[0]);
        uint32_t clr = src[index];
        if (index > 0)
            clr = clr | 0xFF;
        return clr;*/
	}
}
