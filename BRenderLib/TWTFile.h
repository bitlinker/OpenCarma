#pragma once

#include <Common.h>

namespace OpenCarma
{
    namespace BRender
    {
        class TWTHeader
        {
        public:
            uint32_t m_size;
            uint32_t m_numFiles;
        };

        class TWTFileEntry
        {
        public:
            uint32_t m_size;
            char m_name[56];
        };

        class TWTFile
        {
        public:
            TWTFile();
            ~TWTFile();
        };
    }
}