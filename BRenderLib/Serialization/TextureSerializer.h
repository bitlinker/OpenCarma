#pragma once

#include <Common.h>
#include <iostream>

#include <Objects/Pixmap.h>

namespace OpenCarma
{
    namespace BRender
    {
        class BR_API TextureSerializer
        {
        private:
            TextureSerializer() {};
            ~TextureSerializer() {};

        public:
            static void DeserializePixelmap(std::istream& stream, std::vector<PixmapPtr>& pixelmaps);
            static void SerializePixelmap(const PixmapPtr& pal, std::ostream& stream);
        };
    }
}
