#include "OpponentDescription.h"

static const std::string STR_NA_NEVER("never");
static const std::string STR_NA_EAGLE("eagle");
static const std::string STR_NA_HAWK("hawk");
static const std::string STR_NA_ALL("all");

OpponentDescription::OpponentDescription()
{
}


OpponentDescription::~OpponentDescription()
{
}

OpponentDescription::NetworkAvailability parseNetAvail(std::string& str)
{
    if (str == STR_NA_NEVER)
        return OpponentDescription::NA_NEVER;
    else if (str == STR_NA_EAGLE)
        return OpponentDescription::NA_EAGLE;
    else if (str == STR_NA_HAWK)
        return OpponentDescription::NA_HAWK;
    else if (str == STR_NA_ALL)
        return OpponentDescription::NA_ALL;
    
    return OpponentDescription::NA_NEVER; // TODO
    //throw 
}


void OpponentDescription::read(TextReader& reader)
{
    // TODO: throw on error
    reader.readLine(m_opponentName);
    reader.readLine(m_driverName);
    m_id = reader.readUInt32();
    m_strength = reader.readUInt32();
    std::string m_avail;
    reader.readLine(m_avail);
    m_networkAvail = parseNetAvail(m_avail);
    reader.readLine(m_flic1File);
    reader.readLine(m_textfFile);
    reader.readLine(m_flic2File);
    uint32_t descrChunksCnt = reader.readUInt32();
    for (uint32_t i = 0; i < descrChunksCnt; ++i)
    {
        DescrTextChunk chunk;
        chunk.read(reader);
    }
}

// TODO: different file
DescrTextChunk::DescrTextChunk()
{
}

DescrTextChunk::~DescrTextChunk()
{
}

void DescrTextChunk::read(TextReader& reader)
{
    std::string offsets;
    reader.readLine(offsets);

    std::string frames;
    reader.readLine(frames);

    uint32_t numLines = reader.readUInt32();
    m_descrText.clear();
    for (uint32_t i = 0; i < numLines; ++i)
    {
        std::string line;
        m_descrText += reader.readLine(line);
        m_descrText.append(line).append("\n");
    }
}