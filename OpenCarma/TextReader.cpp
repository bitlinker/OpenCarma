#include <TextReader.h>

TextReader::TextReader(std::istream& stream, TextDecoder::DecoderType decoderType)
: m_stream(stream)
, m_decoder(decoderType)
{
}


TextReader::~TextReader()
{
}

bool TextReader::readLine(std::string& line)
{
    while (true)
    {
        if (!readLineRaw(line))
            return false;

        // Trim comments
        std::string::size_type comment = line.find("//");
        if (comment != std::string::npos)
            line.resize(comment);

        // Trim whitespaces
        line.erase(line.find_last_not_of(" \n\r\t") + 1);        

        if (line.empty())
            continue;        

        break;
    }
    
    return true;
}

bool TextReader::readLineRaw(std::string& line)
{
    std::string srcLine;
    std::getline(m_stream, srcLine);

    return m_decoder.decodeLine(srcLine, line);
}

bool TextReader::isEOF()
{
    return m_stream.eof();
}

uint32_t TextReader::readUInt32()
{
    // TODO: exceptions?
    std::string line;
    if (!readLine(line))
        return -1;
    
    try
    {
        return static_cast<uint32_t>(std::stoi(line));
    }
    catch (const std::invalid_argument& e)
    {
        return -1; // TODO
    }    
}
