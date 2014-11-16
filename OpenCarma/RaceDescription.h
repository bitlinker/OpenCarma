#pragma once
#include <string>

class RaceDescription
{
public:
    RaceDescription();
    ~RaceDescription();
private:
    std::string m_name;
    std::string m_flics[3];
    std::string m_textDescription;
    // TODO: Text chunks
};
