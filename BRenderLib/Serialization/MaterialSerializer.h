#pragma once

#include <Common.h>
#include <iostream>

#include <Objects/Material.h>

namespace OpenCarma
{
    namespace BRender
    {
        class BR_API MaterialSerializer
        {
        private:
            MaterialSerializer() {};
            ~MaterialSerializer() {};

        public:
            static void DeserializeMaterial(std::istream& stream, std::vector<MaterialPtr>& materials);
            static void SerializeMaterial(const MaterialPtr& pal, std::ostream& stream);
        };
    }
}
