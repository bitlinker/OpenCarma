#include "OpponentTxt.h"

static const std::string STR_NA_NEVER("never");
static const std::string STR_NA_EAGLE("eagle");
static const std::string STR_NA_HAWK("hawk");
static const std::string STR_NA_ALL("all");

OpponentTxt::OpponentTxt()
{
}


OpponentTxt::~OpponentTxt()
{
}

OpponentTxt::NetworkAvailability parseNetAvail(std::string& str)
{
    if (str == STR_NA_NEVER)
        return OpponentTxt::NA_NEVER;
    else if (str == STR_NA_EAGLE)
        return OpponentTxt::NA_EAGLE;
    else if (str == STR_NA_HAWK)
        return OpponentTxt::NA_HAWK;
    else if (str == STR_NA_ALL)
        return OpponentTxt::NA_ALL;
    
    return OpponentTxt::NA_NEVER; // TODO
    //throw 
}


void OpponentTxt::read(TextReader& reader)
{
    // TODO: throw on error
    reader.readLine(m_opponentName);
    reader.readLine(m_driverName);
    reader.readUInt32(m_id);
    reader.readUInt32(m_strength);
    std::string m_avail;
    reader.readLine(m_avail);
    m_networkAvail = parseNetAvail(m_avail);
    reader.readLine(m_flic1File);
    reader.readLine(m_textfFile);
    reader.readLine(m_flic2File);
	uint32_t descrChunksCnt = 0;
    reader.readUInt32(descrChunksCnt);
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

	uint32_t numLines = 0;
	reader.readUInt32(numLines);
    m_descrText.clear();
    for (uint32_t i = 0; i < numLines; ++i)
    {
        std::string line;
		reader.readLine(line);
        m_descrText.append(line).append("\n");
    }
}