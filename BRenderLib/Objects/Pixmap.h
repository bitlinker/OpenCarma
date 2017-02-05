#pragma once
#include <Common.h>

namespace OpenCarma
{
    namespace BRender
    {
        class BR_API Pixmap
        {
        public:
            enum PixelFormat 
            {
                // Each pixel is an index into a color map
                BR_PMT_INDEX_1 = 0,
                BR_PMT_INDEX_2,
                BR_PMT_INDEX_4,
                BR_PMT_INDEX_8,
                // True color RGB
                BR_PMT_RGB_555,		/* 16 bits per pixel */
                BR_PMT_RGB_565,		/* 16 bits per pixel */
                BR_PMT_RGB_888,		/* 24 bits per pixel */
                BR_PMT_RGBX_888,	/* 32 bits per pixel */
                BR_PMT_RGBA_8888,	/* 32 bits per pixel */   
                // YUV
                BR_PMT_YUYV_8888,
                BR_PMT_YUV_888,
                // Depth
                BR_PMT_DEPTH_16,
                BR_PMT_DEPTH_32,
                // Opacity
                BR_PMT_ALPHA_8,
                // Opacity + Index
                BR_PMT_INDEXA_88,

                BR_PMT_MAX
            };

        public:
            Pixmap(PixelFormat format, uint32_t width, uint32_t height, int32_t stride);

            PixelFormat getPixelFormat() const { return static_cast<PixelFormat>(mPixelFormat); }
            int32_t getStride() const { return mStride; }
            uint32_t getWidth() const { return mWidth; }
            uint32_t getHeight() const { return mHeight; }

            void setXOffset(int32_t offset) { mOffsetX = offset; }
            void setYOffset(int32_t offset) { mOffsetY = offset; }
            int32_t getXOffset() const { return mOffsetX; }
            int32_t getYOffset() const { return mOffsetY; }

            uint32_t getBpp() const;

            const std::string& getName() const { return mName; }
            void setName(const std::string& name) { mName = name; }

            uint32_t getRawSize() const { return mData.size(); }
            uint8_t* getRawBuf() { return &mData[0]; }
            const uint8_t* getRawBufConst() const { return &mData[0]; }

            inline const std::vector<uint8_t>& getPixels() const
            {
                return mData;
            }

            inline uint8_t getColorPAL8(uint32_t index) const
            {
                return mData[index];
            }

            inline uint32_t getColorARGB(uint32_t index) const
            {
                return reinterpret_cast<const uint32_t*>(&mData[0])[index];
            }

        private:
            PixelFormat mPixelFormat;
			int16_t mStride;
            uint16_t mWidth;
            uint16_t mHeight;
			int16_t mOffsetX;
			int16_t mOffsetY;
			std::string mName;
			std::vector<uint8_t> mData;
        };

        typedef std::shared_ptr<Pixmap> PixmapPtr;
    }
}
