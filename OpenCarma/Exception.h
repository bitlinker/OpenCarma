#pragma once
#include <string>

class Exception
{
public:
    Exception(const std::string& what)
        : m_what(what)
    {
    }

    virtual ~Exception() 
    {
    }

    inline const std::string& what() const
    {
        return m_what;
    }

private:
    std::string m_what;
};

class UnknownException : public Exception
{
public:
    UnknownException(const std::string& what)
    : Exception(what)
    {
    }

    virtual ~UnknownException()
    {
    };
};

class IOException : public Exception
{
public:
    IOException(const std::string& what)
    : Exception(what)
    {
    }

    virtual ~IOException()
    {
    };
};
