#pragma once
#include "Common.h"

namespace OpenCarma
{
    namespace BRender
    {
        class BR_API ObjectFactory
        {
        public:
            ObjectFactory();
            ~ObjectFactory();

            bool load(std::string& filename);
        };
    }
}