#pragma once
#include <string>
#include <stdint.h>

// TODO: move to common carma lib?
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

    bool decodeLine(const std::string& inStr, std::string& outStr) const;

private:
    uint8_t* m_textDecodeTable;
    uint8_t* m_commentDecodeTable;
};