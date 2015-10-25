#include <TextReader.h>
#include <sstream>
#include <Exception/Exception.h>

inline static uint32_t ParseUint32(const std::string& str)
{
	bool isHex = str.compare(0, 2, "0x") == 0;
	return static_cast<uint32_t>(std::stoi(str, 0, isHex ? 16 : 10));
}

inline static uint32_t ParseSInt32(const std::string& str)
{
	return static_cast<int32_t>(std::stoi(str, 0, 10));
}

inline static float ParseFloat(const std::string& str)
{
	return static_cast<float>(std::stof(str));
}

TextReader::TextReader(std::istream& stream, TextDecoder::DecoderType decoderType)
: m_stream(stream)
, m_decoder(decoderType)
{
}

TextReader::~TextReader()
{
}

void TextReader::readLine(std::string& line) const
{
    while (true)
    {
		readLineRaw(line);

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
}

void TextReader::readLineRaw(std::string& line) const
{
	if (isEOF())
		throw Commons::EOFException("EOF reached");

    std::string srcLine;
    std::getline(m_stream, srcLine);

    if (!m_decoder.decodeLine(srcLine, line))
		throw Commons::IOException("String decoding failed");
}

bool TextReader::isEOF() const
{
    return m_stream.eof();
}

void TextReader::readUInt32(uint32_t& value) const
{
	std::string line;
	readLine(line);
	value = ParseUint32(line);
}

void TextReader::readSInt32(int32_t& value) const
{
	std::string line;
	readLine(line);
	value = ParseSInt32(line);
}

void TextReader::readFloat(float& value) const
{
	std::string line;
	readLine(line);
	value = ParseFloat(line);
}

void TextReader::readUInt32Vec(uint32_t* ptr, uint32_t count) const
{
	std::string line; // TODO: copy-paste
	readLine(line);

	std::stringstream ss(line);
	for (uint32_t i = 0; i < count; ++i)
	{
		if (!ss.good())
			throw Commons::IOException("Wrong number of values in string");

		std::string tmp;
		std::getline(ss, tmp, ',');
		*ptr++ = ParseUint32(tmp);
	}
}

void TextReader::readUInt32Vec(std::vector<uint32_t>& vec) const
{
	vec.clear();
	std::string line;
	readLine(line);

	std::stringstream ss(line);
	while (ss.good())
	{
		std::string tmp;
		std::getline(ss, tmp, ',');
		uint32_t value = ParseUint32(tmp);
		vec.push_back(value);
	}
}

void TextReader::readFloatVec(float* ptr, uint32_t count) const
{
	std::string line;
	readLine(line);

	std::stringstream ss(line);
	for (uint32_t i = 0; i < count; ++i)
	{
		if (!ss.good())
			throw Commons::IOException("Wrong number of values in string");

		std::string tmp;
		std::getline(ss, tmp, ',');
		*ptr++ = ParseFloat(tmp);
	}
}

void TextReader::readFloatVec(std::vector<float>& vec) const
{
	// TODO: copy-paste
	vec.clear();
	std::string line;
	readLine(line);

	std::stringstream ss(line);
	while (ss.good())
	{
		std::string tmp;
		std::getline(ss, tmp, ',');
		float value = ParseFloat(tmp);
		vec.push_back(value);
	}
}

void TextReader::readUInt32_2(uint32_t& v1, uint32_t& v2) const
{
	std::vector<uint32_t> vals;
	readUInt32Vec(vals);
	if (vals.size() != 2)
		throw Commons::IOException("Wrong number of values in string");

	v1 = vals[0];
	v2 = vals[1];
}

// TODO: replace with array version
void TextReader::readUInt32_3(uint32_t& v1, uint32_t& v2, uint32_t& v3) const
{
	std::vector<uint32_t> vals;
	readUInt32Vec(vals);
	if (vals.size() != 3)
		throw Commons::IOException("Wrong number of values in string");

	v1 = vals[0];
	v2 = vals[1];
	v3 = vals[2];
}

void TextReader::readFloat_2(float& v1, float& v2) const
{
	std::vector<float> vals;
	readFloatVec(vals);
	if (vals.size() != 2)
		throw Commons::IOException("Wrong number of values in string");

	v1 = vals[0];
	v2 = vals[1];
}

void TextReader::skipLines(uint32_t numLines) const
{
	std::string line;
	for (uint32_t i = 0; i < numLines; ++i)
		readLine(line);
}