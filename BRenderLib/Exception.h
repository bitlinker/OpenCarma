#pragma once
#include <Common.h>

namespace OpenCarma
{
    class UnknownException : public std::runtime_error
    {
    public:
        UnknownException(const std::string& what)
            : std::runtime_error(what)
        {
        }
    };
    
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

    class GLException : public std::runtime_error
    {
    public:
        GLException(const std::string& what)
            : std::runtime_error(what)
        {
        }
    };
}
