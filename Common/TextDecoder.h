#pragma once
#include <string>
#include <stdint.h>

class TextDecoder
{
public:
    enum DecoderType
    {
        DT_CARMA1_DEMO,
        DT_CARMA1,
        // TODO: splat, splat demo, c2 ???
    };

    TextDecoder(DecoderType type);
    ~TextDecoder();

    bool decodeLine(const std::string& inStr, std::string& outStr);

private:
    uint8_t* m_textDecodeTable;
    uint8_t* m_commentDecodeTable;
};