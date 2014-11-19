#include <iostream>
#include <Render.h>
#include <Init.h>
#include <Exception.h>


//
//#include <TextReader.h>
//#include <OpponentDescription.h>
//
//static bool ReadOpponentsTxt(TextReader& reader)
//{
//    uint32_t numOpponents = reader.readUInt32();
//    for (uint32_t i = 0; i < numOpponents; ++i)
//    {
//        OpponentDescription descr;
//        descr.read(reader);
//    }
//
//    std::string endMarker;
//    reader.readLine(endMarker);
//
//    if (endMarker != "END")
//        return false;
//
//    return true;
//}

//blkeagle.txt

/*int main(int argc, char **argv)
{
std::string inFileName(argv[2]);
std::ifstream iStrm;
iStrm.open(inFileName, std::ios_base::in);
if (!iStrm.is_open())
{
std::cout << "Can't open file for reading: " << inFileName << std::endl;
return -1;
}

TextReader reader(iStrm, TextDecoder::DT_CARMA1);

if (!ReadOpponentsTxt(reader))
{
std::cout << "Can't read opponents.txt" << std::endl;
return -1;
}

return 0;
}*/

#include <Serialization/ModelSerializer.h>
#include <Serialization/TextureSerializer.h>
#include <Serialization/PaletteSerializer.h>
#include <Serialization/MaterialSerializer.h>
#include <fstream>

int main(int argc, char **argv)
{
    using namespace OpenCarma;
    using namespace OpenCarma::BRender;

    try
    {
        std::cout << "Initializing Carma" << std::endl;

        Init init;
        Render render;

        // TODO Load mdl
        std::vector<ModelPtr> models;
        std::ifstream strm_model("e:\\Games\\Carma\\DATA\\MODELS\\EAGBLAK.DAT", std::ifstream::binary);
        ModelSerializer::DeserializeModels(strm_model, models);

        std::ifstream strm_palette("e:\\Games\\Carma\\DATA\\REG\\PALETTES\\DRRENDER.PAL", std::ifstream::binary);
        PalettePtr palette = PaletteSerializer::DeserializePalette(strm_palette);
    
        std::vector<PixmapPtr> pixelmaps;
        std::ifstream strm_pixmaps("e:\\Games\\Carma\\DATA\\PIXELMAP\\EAGREDL8.PIX", std::ifstream::binary);
        TextureSerializer::DeserializePixelmap(strm_pixmaps, pixelmaps);

        std::vector<MaterialPtr> materials;
        std::ifstream strm_material("e:\\Games\\Carma\\DATA\\MATERIAL\\AGENTO.MAT", std::ifstream::binary);
        MaterialSerializer::DeserializeMaterial(strm_material, materials);

        render.getTextureManager().load(pixelmaps, palette);

        while (render.tick(0.F))
        {
        }

        std::cout << "Carma finished" << std::endl;
        return 0;
    }
    catch (const Exception& e)
    {
        std::cout << "Exception occurred: " << e.what() << std::endl;
        return -1;
    }    
}