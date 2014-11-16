#pragma once

#include <Common.h>
#include <iostream>

#include <Objects/Palette.h>

namespace OpenCarma
{
    namespace BRender
    {
        class BR_API PaletteSerializer
        {
        private:
            PaletteSerializer() {};
            ~PaletteSerializer() {};

        public:
            static PalettePtr DeserializePalette(std::istream& stream);
            static void SerializePalette(const PalettePtr& pal, std::ostream& stream);
        };
    }
}
