#include "TextDecoder.h"

// Carma 1:

// Demo version file decoding table (both text & comment)
static uint8_t gCarma1DemoTable[] =
{
    0x58, 0x50, 0x3A, 0x76, 0xCB, 0xB6, 0x85, 0x65,
    0x15, 0xCD, 0x5B, 0x07, 0xB1, 0x68, 0xDE, 0x3A
};

// Text decoding table
static uint8_t gCarma1TextTable[] =
{
    0x6C, 0x1B, 0x99, 0x5F, 0xB9, 0xCD, 0x5F, 0x13,
    0xCB, 0x04, 0x20, 0x0E, 0x5E, 0x1C, 0xA1, 0x0E
};

// Comment decoding table
static uint8_t gCarma1CommentTable[] =
{
    0x67, 0xA8, 0xD6, 0x26, 0xB6, 0xDD, 0x45, 0x1B,
    0x32, 0x7E, 0x22, 0x13, 0x15, 0xC2, 0x94, 0x37
};

TextDecoder::TextDecoder(DecoderType type)
: m_textDecodeTable(NULL)
, m_commentDecodeTable(NULL)
{
    switch (type)
    {
    case DT_CARMA1:
        m_textDecodeTable = gCarma1TextTable;
        m_commentDecodeTable = gCarma1CommentTable;
        break;
    case DT_CARMA1_DEMO:
        m_textDecodeTable = gCarma1DemoTable;
        m_commentDecodeTable = NULL;
        break;
    }
}

TextDecoder::~TextDecoder()
{
}

bool TextDecoder::decodeLine(const std::string& inStr, std::string& outStr) const
{
    if (!m_textDecodeTable)
        return false;

    outStr = inStr;

    size_t srcLen = inStr.length();
    if (srcLen == 0)
        return true;

    uint8_t* pData = reinterpret_cast<uint8_t*>(&outStr[0]);
    if (pData[0] == '@') // Line encrypted
    {
        bool bComment = false;

        uint32_t c = (srcLen - 1) % 16;
        uint8_t decoded = 0;

        for (size_t i = 1; i < srcLen; ++i)
        {
            if (pData[i] == 9) // Spaces fix
                pData[i] = 0x9f;

            if (m_commentDecodeTable && i >= 3 && outStr[i - 3] == '/' && outStr[i - 2] == '/')
                bComment = true;

            if (bComment)
                decoded = (((pData[i] - 0x20) ^ m_commentDecodeTable[c]) & 0x7f) + 0x20;
            else
                decoded = (((pData[i] - 0x20) ^ m_textDecodeTable[c]) & 0x7f) + 0x20;

            if (decoded == 0x9f)  // Spaces fix
                decoded = 9;
            pData[i - 1] = (char)decoded;

            c = (c + 7) % 16;
        }

        // Unknown fix. Not used in demo files
        for (size_t x = 0; x < srcLen; x++)
        {
            if (pData[x] == 0x80)
                pData[x] = 0x20;
        }

        outStr.resize(srcLen - 1);
    }
    else
        outStr.resize(srcLen);

    return true;
}