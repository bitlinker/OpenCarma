#pragma once
#include <string>
#include <iostream>
#include <TextDecoder.h>

class TextReader
{
public:
    TextReader(std::istream& stream, TextDecoder::DecoderType decoderType);
    ~TextReader();

    //! Reads and decodes only meaningful lines, clearing out empty lines, comments, whitespaces
    bool readLine(std::string& line);

    //! Reads and decodes a single RAW line
    bool readLineRaw(std::string& line);

    uint32_t readUInt32();

    bool isEOF();
    
private:
    std::istream& m_stream;
    TextDecoder m_decoder;
};

