#pragma once
#include "Common.h"

namespace OpenCarma
{
    namespace BRender
    {
        class BR_API Object
        {
        public:
            Object();
            virtual ~Object();

            virtual bool fromBuf() { return true; }
        };
    }
}
