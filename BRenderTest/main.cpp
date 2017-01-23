#include <iostream>
#include <fstream>
#include <cassert>

#include <Imaging/TgaImageEncoder.h>
#include <Streams/FileStream.h>
#include <Serialization/PixmapSerializer.h>
#include <Serialization/ModelSerializer.h>
#include <Exception/Exception.h>

using namespace Commons;
using namespace Commons::Imaging;
using namespace OpenCarma::BRender;

static void WritePixmap2Tga(const std::string& filename, const PixmapPtr& pixmap, const PixmapPtr& pal)
{    
    assert(pixmap->getPixelFormat() == Pixmap::BR_PMT_INDEX_8);
    assert(pal->getPixelFormat() == Pixmap::BR_PMT_RGBA_8888);

    uint32_t width = pixmap->getWidth();
    uint32_t height = pixmap->getHeight();

    const uint8_t* src = &pixmap->getPixels()[0];
    std::vector<uint32_t> rgbPixmap(width * height);    

    for (uint32_t y = 0; y < height; ++y)
    {
        uint32_t* dst = &rgbPixmap[(height - y - 1) * width];

        for (uint32_t x = 0; x < width; ++x)
        {
            const uint32_t srcColor = pal->getColorARGB(*src++);
            const uint8_t* srcChannel = reinterpret_cast<const uint8_t*>(&srcColor);
            uint8_t *dstChannel = reinterpret_cast<uint8_t*>(dst++);
            
            dstChannel[0] = srcChannel[3]; // B
            dstChannel[1] = srcChannel[2]; // G
            dstChannel[2] = srcChannel[1]; // R
            dstChannel[3] = srcChannel[0]; // A
        }
    }

    FileStreamPtr streamPtr(new FileStream(filename, FileStream::MODE_WRITE));
    TgaImageEncoder encoder;
    ImageInfo info(width, height, 4);
    encoder.writeImage(streamPtr, info, (uint8_t*)&rgbPixmap[0]);
}

int main(int argc, char **argv)
{    
    std::cout << "BRender test" << std::endl;

	if (argc < 2) 
	{
		std::cout << "Usage: BRenderTest [carmaPath]" << std::endl;
		return -1;
	}

	std::string carmaPath(argv[1]);

    // TODO: try/catch
    try
    {
		std::vector<PixmapPtr> palletes;
        IOStreamPtr strm_pal(new FileStream(carmaPath + "/DATA/REG/PALETTES/DRRENDER.PAL", FileStream::MODE_READ));
		PixmapSerializer::DeserializePixelmap(strm_pal, palletes);

        IOStreamPtr strm_pixmap(new FileStream(carmaPath + "/DATA/PIXELMAP/DEZRACE2.PIX", FileStream::MODE_READ));

        std::vector<PixmapPtr> pixelMaps;
        PixmapSerializer::DeserializePixelmap(strm_pixmap, pixelMaps);

        int k = 0;

        //WritePixmap2Tga("d:/test.tga", pixelMaps[1], pal);

        /*FileStream strm_mat("e:/Games/Carma/DATA/MATERIAL/MERC8.MAT");
        auto mat = TextureSerializer::DeserializeMaterial(strm_mat);*/

        /*std::vector<ModelPtr> models;
        std::ifstream strm_model("e:\\Games\\Carma\\DATA\\MODELS\\EAGBLAK.DAT", std::ifstream::binary);
        ModelSerializer::DeserializeModels(strm_model, models);        */
    }
    catch (const SerializationException se)
    {
        std::cout << "Serialization exception: " << se.what() << std::endl;
    }
    catch (const IOException& ioe)
    {
        std::cout << "IO Exception: " << ioe.what() << std::endl;
    }
    
    

    return 0;
}