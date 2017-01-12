#include <iostream>
#include <fstream>
#include <TextDecoder.h>

int main(int argc, char **argv)
{
    std::cout << "Carmageddon text decoder" << std::endl;

    if (argc < 3 || argc > 4)
    {
        std::cout << "Usage: TextDecoder GameType EncodedFile.txt [DecodedFile.txt]" << std::endl;
        std::cout << "\t GameType is one of the following: carma1demo; carma1" << std::endl;
        std::cout << "\t Default DecodedFile.txt is EncodedFile.txt_decoded.txt" << std::endl;
        return -1;
    }

    TextDecoder::DecoderType type;
    std::string decoderStr(argv[1]);
    if (decoderStr == "carma1demo")
        type = TextDecoder::DT_CARMA1_DEMO;
    else if (decoderStr == "carma1")
        type = TextDecoder::DT_CARMA1;
    else
    {
        std::cout << "Unknown decoder type: " << decoderStr << std::endl;
        return -1;
    }

    std::string inFileName(argv[2]);
    std::string outFileName;
    if (argc > 3)
        outFileName = std::string(argv[3]);
    else
        outFileName = inFileName + "_decoded.txt";

    std::ifstream iStrm;
    iStrm.open(inFileName.c_str(), std::ios_base::in);
    if (!iStrm.is_open())
    {
        std::cout << "Can't open file for reading: " << inFileName << std::endl;
        return -1;
    }

    std::ofstream oStrm;
    oStrm.open(outFileName.c_str(), std::ios_base::out);
    if (!oStrm.is_open())
    {
        std::cout << "Can't open file for writing: " << outFileName << std::endl;
        return -1;
    }

    TextDecoder decoder(type);

    std::string src;
    std::string dest;

    while (!iStrm.eof())
    {
        std::getline(iStrm, src);
        if (!decoder.decodeLine(src, dest))
        {
            std::cout << "Can't decode line: " << src << std::endl;
            return -1;
        }

        oStrm << dest << std::endl;
    }

    std::cout << "Decoded: " << outFileName << std::endl;
    return 0;
}