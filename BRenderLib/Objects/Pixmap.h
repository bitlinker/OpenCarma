#pragma once
#include <Common.h>
#include <Objects/ChunkHeader.h>

namespace OpenCarma
{
    namespace BRender
    {
        class BR_API Pixmap
        {
            friend class PixmapSerializer;

        public:
            enum PixelFormat 
            {
                /*
                * Each pixel is an index into a color map
                */
                BR_PMT_INDEX_1,
                BR_PMT_INDEX_2,
                BR_PMT_INDEX_4,
                BR_PMT_INDEX_8,

                /*
                * True color RGB
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

            PixelFormat getPixelFormat() { return static_cast<PixelFormat>(mPixelFormat); }
            int32_t getStride() const { return mStride; }
            uint32_t getWidth() const { return mWidth; }
            uint32_t getHeight() const { return mHeight; }
            int32_t getXOffset() const { return mOffsetX; }
            int32_t getYOffset() const { return mOffsetY; }
            uint32_t getBPP() const { return mBpp; }
            uint32_t getNumPixels() const { return mNumPixels; }
            const std::string& getName() const { return mName; }
            bool isValid() const;

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
			// Texture head:
			uint8_t mPixelFormat;    //!< Pixel format
			int16_t mStride;	     //!< Stride
			uint16_t mWidth;		 //!< Width
			uint16_t mHeight;	     //!< Height
			int16_t mOffsetX;        //!< oX
			int16_t mOffsetY;		 //!< oY
			std::string mName;       //!< Null-terminated name

			// Texture data:
			uint32_t mNumPixels;
			uint32_t mBpp;
			std::vector<uint8_t> mData;
        };

        typedef std::shared_ptr<Pixmap> PixmapPtr;
    }
}
