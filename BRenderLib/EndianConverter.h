#pragma once

namespace OpenCarma
{
    namespace BRender
    {
        class BR_API EndianConverter
        {
        public:
            EndianConverter();
            ~EndianConverter();

            static bool IsArchBigEndian();

            static uint16_t ByteSwapUInt16(uint16_t source);
            static uint32_t ByteSwapUInt32(uint32_t source);
        };
    }
}
