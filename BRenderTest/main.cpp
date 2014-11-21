#include <iostream>
#include <fstream>
#include <cstdio>

#include <Serialization/TextureSerializer.h>
#include <Serialization/PaletteSerializer.h>
#include <Serialization/ModelSerializer.h>
#include <Exception.h>

using namespace OpenCarma::BRender;


static bool Write32BitTga(const string& filename, uint32_t width, uint32_t height, const uint8_t* data)
{
    FILE *fTile;
    fopen_s(&fTile, filename.c_str(), "wb");
    if (!fTile)
        return false;

    putc(0, fTile);
    putc(0, fTile);
    putc(2, fTile);                         /* uncompressed RGB */
    putc(0, fTile); putc(0, fTile);
    putc(0, fTile); putc(0, fTile);
    putc(0, fTile);
    putc(0, fTile); putc(0, fTile);           /* X origin */
    putc(0, fTile); putc(0, fTile);           /* y origin */
    putc((width & 0x00FF), fTile);
    putc((width & 0xFF00) / 256, fTile);
    putc((height & 0x00FF), fTile);
    putc((height & 0xFF00) / 256, fTile);
    putc(32, fTile);                        /* 32 bit bitmap */
    putc(0, fTile);

    fwrite(data, width * height * 4, 1, fTile);
    fclose(fTile);
    return true;
}

static bool WritePixmap2Tga(const string& filename, const PixmapPtr& pixmap, const PalettePtr& pal)
{    
    uint32_t width = pixmap->getWidth();
    uint32_t height = pixmap->getHeight();

    const uint8_t* src = &pixmap->getPixels()[0];
    std::vector<uint32_t> rgbPixmap(width * height);    

    for (uint32_t y = 0; y < height; ++y)
    {
        uint32_t* dst = &rgbPixmap[(height - y - 1) * width];

        for (uint32_t x = 0; x < width; ++x)
        {
            const uint32_t srcColor = pal->getColor(*src++);
            const uint8_t* srcChannel = reinterpret_cast<const uint8_t*>(&srcColor);
            uint8_t *dstChannel = reinterpret_cast<uint8_t*>(dst++);
            
            dstChannel[0] = srcChannel[3]; // B
            dstChannel[1] = srcChannel[2]; // G
            dstChannel[2] = srcChannel[1]; // R
            dstChannel[3] = srcChannel[0]; // A
        }
    }
    
    return Write32BitTga(filename, width, height, (uint8_t*)&rgbPixmap[0]);
}



int main()
{    
    std::cout << "BRender test" << std::endl;

    //ObjectFactory factory;
    //bool bRes = factory.load(std::string());

    // TODO: try/catch
    try
    {
        /*std::ifstream strm_pal("e:/Games/Carma/DATA/REG/PALETTES/DRRENDER.PAL", std::ifstream::binary);
        auto pal = PaletteSerializer::DeserializePalette(strm_pal);

        std::ifstream strm_pixmap("e:/Games/Carma/DATA/PIXELMAP/DEZRACE2.PIX", std::ifstream::binary);
        //FileStream strm_pixmap("e:/Games/Carma/DATA/PIXELMAP/DEZRACE2.PIX");

        std::vector<PixmapPtr> pixelMaps;
        TextureSerializer::DeserializePixelmap(strm_pixmap, pixelMaps);

        WritePixmap2Tga("d:/test.tga", pixelMaps[1], pal);*/

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
        std::cout << "IO Exception" << ioe.what() << std::endl;
    }
    
    

    return 0;
}