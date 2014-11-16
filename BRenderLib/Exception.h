#pragma once
#include <Common.h>

namespace OpenCarma
{
    namespace BRender
    {
        class IOException : public std::runtime_error
        {
        public:
            IOException(const string& what)
                : std::runtime_error(what)
            {
                }
        };

        class SerializationException : public std::runtime_error
        {
        public:
            SerializationException(const string& what)
                : std::runtime_error(what)
            {
                }
        };
    }
}
