#include "ObjectFactory.h"

namespace OpenCarma
{
    namespace BRender
    {
        ObjectFactory::ObjectFactory()
        {
        }


        ObjectFactory::~ObjectFactory()
        {
        }

        bool ObjectFactory::load(std::string& filename)
        {
            // TODO: iostream
            FILE *f = fopen(filename.c_str(), "rb");
            if (!f)
                return false;

            fseek(f, 0L, SEEK_END);
            size_t length = ftell(f);
            fseek(f, 0L, SEEK_SET);

            std::vector<uint8_t> data;
            data.resize(length);
            fread(&data[0], length, 1, f);

            // TODO: load data

            // read chunk
            // check it 
            // read next;


            fclose(f);
            return true;
        }
    }
}