#include <BigEndianStreamReader.h>
#include <Common/EndianUtils.h>
#include <Exception/Exception.h>


namespace OpenCarma
{
    namespace BRender
    {
        BigEndianStreamReader::BigEndianStreamReader(std::istream& stream)
            : m_stream(stream)
        {
            // TODO: endian detection
            //bool archBigEndian = EndianConverter::IsArchBigEndian();
            m_stream.exceptions(std::istream::failbit | std::istream::badbit);
        }

        BigEndianStreamReader::~BigEndianStreamReader()
        {
        }

        static std::ios_base::seek_dir TranslateOrigin(BigEndianStreamReader::SeekOrigin origin)
        {
            switch (origin)
            {
            case BigEndianStreamReader::SeekOrigin_SET:
                return std::ios_base::beg;
                break;
            case BigEndianStreamReader::SeekOrigin_CUR:
                return std::ios_base::cur;
                break;
            case BigEndianStreamReader::SeekOrigin_END:
                return std::ios_base::end;
                break;
            default:
                throw std::istream::failure("Unknown seek origin");
            }
        }

        void BigEndianStreamReader::seek(int32_t size, SeekOrigin origin)
        {
            m_stream.seekg(size, TranslateOrigin(origin));
        }

        void BigEndianStreamReader::read(uint8_t* buf, size_t size)
        {
            m_stream.read(reinterpret_cast<char*>(buf), size);
        }

        void BigEndianStreamReader::write(uint8_t* buf, size_t size)
        {
            m_stream.read(reinterpret_cast<char*>(buf), size);
        }

        bool BigEndianStreamReader::isEOF()
        {
            m_stream.peek();
            return m_stream.eof();
        }

        uint32_t BigEndianStreamReader::tell()
        {
            return static_cast<uint32_t>(m_stream.tellg());
        }

        uint32_t BigEndianStreamReader::readUInt32()
        {
            uint32_t origVal;
            m_stream.read(reinterpret_cast<char*>(&origVal), sizeof(origVal));            
            return Commons::EndianUtils::ByteSwapUInt32(origVal); // TODO: if needed
        }

        uint16_t BigEndianStreamReader::readUInt16()
        {
            uint16_t origVal;
            m_stream.read(reinterpret_cast<char*>(&origVal), sizeof(origVal));
            return Commons::EndianUtils::ByteSwapUInt16(origVal);
        }

        uint8_t BigEndianStreamReader::readUInt8()
        {
            uint8_t value;
            m_stream.read(reinterpret_cast<char*>(&value), sizeof(value));
            return value;
        }

        float BigEndianStreamReader::readFloat()
        {
            uint32_t origVal;
            m_stream.read(reinterpret_cast<char*>(&origVal), sizeof(origVal));
            origVal = Commons::EndianUtils::ByteSwapUInt32(origVal);
            return *reinterpret_cast<float*>(&origVal);
        }

		std::string BigEndianStreamReader::readString()
        {
			std::string res;
            char ch = 0;
            while (true)
            {
                m_stream.read(reinterpret_cast<char*>(&ch), 1);
                if (ch == '\0')
                    break;

                res.push_back(ch);
            }

            return res;
        }
    }
}