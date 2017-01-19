#include <cassert>
#include <Common/StringUtils.h>
#include <Serialization/TextureSerializer.h>
#include <Streams/StreamReader.h>
#include <Exception/Exception.h>

using namespace Commons;

namespace OpenCarma
{
    namespace BRender
    {
        void TextureSerializer::DeserializePixelmap(const IOStreamPtr& stream, std::vector<PixmapPtr>& pixelmaps)
        {
            assert(stream);

            PixmapPtr curPixmap;

            StreamReader reader(stream, Endianness::BIG_ENDIAN);

            // TODO: common code for this stuff
            // TODO: logger
            FileHeaderChunk fileHeader;
            ChunkHeader header;
            IOStream::size_type streamSize = reader.size();
            while (reader.tell() < streamSize)
            {
                header.read(reader);
                uint32_t lastOffset = reader.tell();

                switch (header.getMagic())
                {
                case FileHeaderChunk::MAGIC:
                    fileHeader.read(reader);
                    break;
                case TextureHeadChunk::MAGIC:
                    curPixmap = PixmapPtr(new Pixmap());
                    assert(curPixmap.get()); // TODO: checks, not asserts
                    curPixmap->m_header.read(reader);
                    break;
                case TextureDataChunk::MAGIC:
                    assert(curPixmap.get());
                    curPixmap->m_data.read(reader);
                    break;
                case 0: // Null header
                    assert(header.getSize() == 0);
                    if (!curPixmap.get() || !curPixmap->isValid())
                        throw SerializationException("Pixelmap object is incorrect");
                    pixelmaps.push_back(curPixmap);
                    curPixmap.reset();
                    break;
                default:
                    throw SerializationException(StringUtils::FormatString("Unknown chunk: %d at %d", header.getMagic(), reader.tell()));
                }

                IOStream::size_type redSize = reader.tell() - lastOffset;
                if (redSize != header.getSize())
                {                   
                    throw SerializationException(StringUtils::FormatString("Incorrect chunk size read: required: %d, current %d", header.getSize(), redSize));
                }
            }
        }

        void TextureSerializer::SerializePixelmap(const PixmapPtr& pal, const IOStreamPtr& stream)
        {
            assert(pal);

            if (!stream)
                throw IOException("Stream is not opened");

            // TODO
        }
    }
}