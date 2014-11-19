#include <Common.h>
#include <EndianConverter.h>

namespace OpenCarma
{
    namespace BRender
    {
        EndianConverter::EndianConverter()
        {
        }


        EndianConverter::~EndianConverter()
        {
        }

        bool EndianConverter::IsArchBigEndian()
        {
            short int word = 0x0001;
            char *byte = (char *)&word;
            return byte[0] == 0;
        }

        uint16_t EndianConverter::ByteSwapUInt16(uint16_t source)
        {
            return ((source & 0xff) << 8) | ((source & 0xff00) >> 8);
        }

        uint32_t EndianConverter::ByteSwapUInt32(uint32_t source)
        {
            source = (source & 0x0000FFFF) << 16 | (source & 0xFFFF0000) >> 16;
            source = (source & 0x00FF00FF) << 8 | (source & 0xFF00FF00) >> 8;
            return source;
        }
    }
}