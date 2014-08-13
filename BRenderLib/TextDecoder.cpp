#include <cstdio>
#include <string>
#include <stdint.h>
#include <fstream>

// Demo version file decoding table (both text & comment)
static uint8_t DemoTable[] = 
{
    0x58, 0x50, 0x3A, 0x76, 0xCB, 0xB6, 0x85, 0x65,
    0x15, 0xCD, 0x5B, 0x07, 0xB1, 0x68, 0xDE, 0x3A
};

// Main decoding table
static uint8_t Table1[] =
{
    0x6C, 0x1B, 0x99, 0x5F, 0xB9, 0xCD, 0x5F, 0x13,
    0xCB, 0x04, 0x20, 0x0E, 0x5E, 0x1C, 0xA1, 0x0E
};

// Comment decoding table
static uint8_t Table2[] =
{
    0x67, 0xA8, 0xD6, 0x26, 0xB6, 0xDD, 0x45, 0x1B,
    0x32, 0x7E, 0x22, 0x13, 0x15, 0xC2, 0x94, 0x37
};


// TODO: optimize me
bool DecryptLine(const std::string& source, std::string& dest, const uint8_t* pMainTable, const uint8_t* pCommentTable)
{
    dest = source;

    size_t srcLen = strlen(source.c_str());
    if (srcLen == 0)
        return true;    

    uint8_t* pData = reinterpret_cast<uint8_t*>(&dest[0]);
    if (pData[0] == '@') // Line encrypted
    {
        bool bComment = false;

        uint32_t c = (srcLen - 1) % 16;
        uint8_t decoded = 0;

        for (size_t i = 1; i < srcLen; ++i)
        {           
            if (pData[i] == 9) // Spaces fix
                pData[i] = 0x9f;

            if (pCommentTable && i >= 3 && dest[i - 3] == '/' && dest[i - 2] == '/')
                bComment = true;

            if (pCommentTable && bComment)
                decoded = (((pData[i] - 0x20) ^ pCommentTable[c]) & 0x7f) + 0x20;
            else
                decoded = (((pData[i] - 0x20) ^ pMainTable[c]) & 0x7f) + 0x20;
            
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

        dest.resize(srcLen - 1);
    }
    else
        dest.resize(srcLen);

    return true;
}


bool DecryptTxtLine(std::string source, std::string& dest)
{
    return DecryptLine(source, dest, Table1, Table2);
}

bool DecryptDemoLine(std::string source, std::string& dest)
{
    return DecryptLine(source, dest, DemoTable, DemoTable);
}

int main()
{
    std::ifstream iStrm;
    iStrm.open("d:\\Projects\\Misc\\Decrypt\\CITYA1.TXT", std::ios_base::in);

    std::ofstream oStrm;
    oStrm.open("d:\\Projects\\Misc\\Decrypt\\CITYA1_decoded.TXT", std::ios_base::out);

    std::string src;
    src.resize(1024);
    
    std::string dest;
    while (!iStrm.eof())
    {
        iStrm.getline(&src[0], src.size());        
        DecryptTxtLine(src, dest);
        oStrm.write(dest.c_str(), dest.length());
        oStrm.put('\n');
    }
       

    return 0;
}