#pragma once
#include <string>
#include <stdint.h>
#include <TextReader.h>

class DescrTextChunk
{
public:
    DescrTextChunk();
    ~DescrTextChunk();
    void read(TextReader& reader);

private:
    uint32_t x, y;
    uint32_t startFrame, endFrame;
    std::string m_descrText;
};


class OpponentDescription
{
public:
    enum NetworkAvailability
    {
        NA_NEVER,
        NA_EAGLE,
        NA_HAWK,
        NA_ALL,
    };

public:
    OpponentDescription();
    ~OpponentDescription();
    void read(TextReader& reader);

private:
    std::string m_opponentName;
    std::string m_driverName;
    uint32_t m_id;
    uint32_t m_strength; // 1-5; -1
    NetworkAvailability m_networkAvail;
    std::string m_flic1File;
    std::string m_textfFile;
    std::string m_flic2File;    
};

