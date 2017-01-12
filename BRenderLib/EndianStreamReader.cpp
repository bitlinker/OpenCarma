#include <EndianStreamReader.h>
#include <Common/Endianness.h>
#include <Exception/Exception.h>

using namespace Commons;

namespace OpenCarma {
    namespace BRender {
        EndianStreamReader::EndianStreamReader(std::istream &stream, Endianness::EndiannessType endiannessType)
                : m_stream(stream) {
            // TODO: endian detection
            Endianness::EndiannessType cpuEndianness = Endianness::getCpuEndianness();
            m_stream.exceptions(std::istream::failbit | std::istream::badbit);
        }

        EndianStreamReader::~EndianStreamReader() {
        }

        static std::ios_base::seekdir TranslateOrigin(EndianStreamReader::SeekOrigin origin) {
            switch (origin) {
                case EndianStreamReader::SeekOrigin_SET:
                    return std::ios_base::beg;
                    break;
                case EndianStreamReader::SeekOrigin_CUR:
                    return std::ios_base::cur;
                    break;
                case EndianStreamReader::SeekOrigin_END:
                    return std::ios_base::end;
                    break;
                default:
                    throw std::istream::failure("Unknown seek origin");
            }
        }

        void EndianStreamReader::seek(int32_t size, SeekOrigin origin) {
            m_stream.seekg(size, TranslateOrigin(origin));
        }

        void EndianStreamReader::read(uint8_t *buf, size_t size) {
            m_stream.read(reinterpret_cast<char *>(buf), size);
        }

        void EndianStreamReader::write(uint8_t *buf, size_t size) {
            m_stream.read(reinterpret_cast<char *>(buf), size);
        }

        bool EndianStreamReader::isEOF() {
            m_stream.peek();
            return m_stream.eof();
        }

        uint32_t EndianStreamReader::tell() {
            return static_cast<uint32_t>(m_stream.tellg());
        }

        uint32_t EndianStreamReader::readUInt32() {
            uint32_t origVal;
            m_stream.read(reinterpret_cast<char *>(&origVal), sizeof(origVal));
            if (mNeedSwap) {
                return Commons::Endianness::ByteSwapUInt32(origVal);
            }
            return origVal;
        }

        uint16_t EndianStreamReader::readUInt16() {
            uint16_t origVal;
            m_stream.read(reinterpret_cast<char *>(&origVal), sizeof(origVal));
            if (mNeedSwap) {
                return Commons::Endianness::ByteSwapUInt16(origVal);
            }
            return origVal;
        }

        uint8_t EndianStreamReader::readUInt8() {
            uint8_t value;
            m_stream.read(reinterpret_cast<char *>(&value), sizeof(value));
            return value;
        }

        float EndianStreamReader::readFloat() {
            uint32_t origVal;
            m_stream.read(reinterpret_cast<char *>(&origVal), sizeof(origVal));
            if (mNeedSwap) {
                origVal = Commons::Endianness::ByteSwapUInt32(origVal);
            }
            return *reinterpret_cast<float *>(&origVal);
        }

        std::string EndianStreamReader::readString() {
            std::string res;
            char ch = 0;
            while (true) {
                m_stream.read(reinterpret_cast<char *>(&ch), 1);
                if (ch == '\0')
                    break;

                res.push_back(ch);
            }

            return res;
        }
    }
}