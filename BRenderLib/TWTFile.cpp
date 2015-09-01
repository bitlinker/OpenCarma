#include "TWTFile.h"

namespace OpenCarma
{
    namespace BRender
    {
        TWTFile::TWTFile()
        {
        }


        TWTFile::~TWTFile()
        {
        }

        uint32_t getFileOffset(uint32_t index)
        {
            return 56 * index + 64;
        }
    }
}