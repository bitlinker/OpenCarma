#pragma once

#include <Common.h>
#include <Streams/IOStream.h>

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
            static void DeserializePixelmap(const Commons::IOStreamPtr& stream, std::vector<PixmapPtr>& pixelmaps);
            static void SerializePixelmap(const PixmapPtr& pal, const Commons::IOStreamPtr& stream);
        };
    }
}
