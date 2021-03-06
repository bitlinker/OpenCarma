#pragma once
#include <TextDecoder.h>
#include <string>
#include <iostream>
#include <vector>

class TextReader
{
public:
    // TODO: use my streams...
    TextReader(std::istream& stream, TextDecoder::DecoderType decoderType);
    ~TextReader();

    //! Reads and decodes only meaningful lines, clearing out empty lines, comments, whitespaces
    void readLine(std::string& line) const;

    //! Reads and decodes a single RAW line
    void readLineRaw(std::string& line) const;

	void skipLines(uint32_t numLines) const;

	void readUInt32(uint32_t& value) const;
	void readSInt32(int32_t& value) const;
	void readFloat(float& value) const;

	void readUInt32Vec(uint32_t* ptr, uint32_t count) const;
	void readUInt32Vec(std::vector<uint32_t>& vec) const;
	void readUInt32_2(uint32_t& v1, uint32_t& v2) const;
	void readUInt32_3(uint32_t& v1, uint32_t& v2, uint32_t& v3) const;

	void readFloatVec(std::vector<float>& vec) const;
	void readFloatVec(float* ptr, uint32_t count) const;
	void readFloat_2(float& v1, float& v2) const;

    bool isEOF() const;		
private:
    std::istream& m_stream;
    TextDecoder m_decoder;
};

