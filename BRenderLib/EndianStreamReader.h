#pragma once
#include <Common.h>
#include <iostream>

namespace OpenCarma
{
    namespace BRender
    {
        // TODO: to commons
        // BRender chunk stream reader
        // throws istream::failure
        class BR_API EndianStreamReader
        {
        public:
            enum SeekOrigin
            {
                SeekOrigin_SET,
                SeekOrigin_CUR,
                SeekOrigin_END,
            };
        public:
            EndianStreamReader(std::istream& stream, Endianness::EndiannessType endiannessType);
            ~EndianStreamReader();

            void seek(int32_t size, SeekOrigin origin);
            void read(uint8_t* buf, size_t size);
            void write(uint8_t* buf, size_t size);
            uint32_t tell();
            bool isEOF();
            
            uint32_t readUInt32();
            uint16_t readUInt16();
            uint8_t readUInt8();
            float readFloat();
            std::string readString();

        private:
            std::istream& m_stream;
            bool mNeedSwap;
        };
    }
}
