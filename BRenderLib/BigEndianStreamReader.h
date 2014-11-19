#pragma once
#include <Common.h>
#include <iostream>

namespace OpenCarma
{
    namespace BRender
    {
        // BRender chunk stream reader
        // throws istream::failure
        class BR_API BigEndianStreamReader
        {
        public:
            enum SeekOrigin
            {
                SeekOrigin_SET,
                SeekOrigin_CUR,
                SeekOrigin_END,
            };
        public:
            BigEndianStreamReader(std::istream& stream);
            ~BigEndianStreamReader();

            void seek(int32_t size, SeekOrigin origin);
            void read(uint8_t* buf, size_t size);
            void write(uint8_t* buf, size_t size);
            uint32_t tell();
            bool isEOF();
            
            uint32_t readUInt32();
            uint16_t readUInt16();
            uint8_t readUInt8();
            float readFloat();
            string readString();

        private:
            std::istream& m_stream;
        };
    }
}
