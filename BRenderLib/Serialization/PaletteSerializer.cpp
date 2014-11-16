#include <cassert>
#include <sstream>
#include <Serialization/PaletteSerializer.h>
#include <BigEndianStreamReader.h>
#include <Exception.h>

namespace OpenCarma
{
    namespace BRender
    {
        PalettePtr PaletteSerializer::DeserializePalette(std::istream& stream)
        {
            if (!stream)
                throw IOException("Stream is not opened");

            PalettePtr pal(new Palette());

            BigEndianStreamReader reader(stream);

            FileHeaderChunk fileHeader;
            ChunkHeader header;
            while (true)
            {
                header.read(reader);
                if (reader.isEOF())
                    break;

                uint32_t lastOffset = reader.tell();

                if (header.getMagic() == FileHeaderChunk::MAGIC)
                {
                    fileHeader.read(reader);
                }
                else if (header.getMagic() == TextureHeadChunk::MAGIC)
                {
                    pal->m_header.read(reader);
                }
                else if (header.getMagic() == TextureDataChunk::MAGIC)
                {
                    pal->m_data.read(reader);
                }
                else if (header.isNULL())
                {
                    continue;
                }
                else
                {
                    std::stringstream ss;
                    ss << "Unknown chunk: " << header.getMagic() << " at " << reader.tell();
                    throw SerializationException(ss.str());
                }

                uint32_t redSize = reader.tell() - lastOffset;
                if (redSize != header.getSize())
                {
                    std::stringstream ss;
                    ss << "Incorrect chunk size red: required: " << header.getSize() << " current " << redSize;
                    throw SerializationException(ss.str());
                }
            }

            if (!pal->isValid())
                throw SerializationException("Palette object is incorrect");

            return pal;
        }

        void PaletteSerializer::SerializePalette(const PalettePtr& pal, std::ostream& stream)
        {
            assert(pal);

            if (!stream)
                throw IOException("Stream is not opened");

            // TODO
        }
    }
}