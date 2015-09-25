#include <cassert>
#include <sstream>
#include <Serialization/TextureSerializer.h>
#include <BigEndianStreamReader.h>
#include <Exception/Exception.h>

namespace OpenCarma
{
    namespace BRender
    {
        void TextureSerializer::DeserializePixelmap(std::istream& stream, std::vector<PixmapPtr>& pixelmaps)
        {
            if (!stream)
                throw Commons::IOException("Stream is not opened");

            PixmapPtr curPixmap;

            BigEndianStreamReader reader(stream);

            FileHeaderChunk fileHeader;
            ChunkHeader header;
            while (!reader.isEOF())
            {
                header.read(reader);                

                uint32_t lastOffset = reader.tell();

                if (header.getMagic() == FileHeaderChunk::MAGIC)
                {
                    fileHeader.read(reader);
                }
                else if (header.getMagic() == TextureHeadChunk::MAGIC)
                {
                    curPixmap = PixmapPtr(new Pixmap());
                    assert(curPixmap.get());
                    curPixmap->m_header.read(reader);
                }
                else if (header.getMagic() == TextureDataChunk::MAGIC)
                {
                    assert(curPixmap.get());
                    curPixmap->m_data.read(reader);
                }
                else if (header.isNULL())
                {
                    if (!curPixmap.get() || !curPixmap->isValid())
                        throw Commons::SerializationException("Pixelmap object is incorrect");
                    pixelmaps.push_back(curPixmap);
                    curPixmap.reset();
                }
                else
                {
                    std::stringstream ss;
                    ss << "Unknown chunk: " << header.getMagic() << " at " << reader.tell();
                    throw Commons::SerializationException(ss.str());
                }

                uint32_t redSize = reader.tell() - lastOffset;
                if (redSize != header.getSize())
                {
                    std::stringstream ss;
                    ss << "Incorrect chunk size red: required: " << header.getSize() << " current " << redSize;
                    throw Commons::SerializationException(ss.str());
                }
            }
        }

        void TextureSerializer::SerializePixelmap(const PixmapPtr& pal, std::ostream& stream)
        {
            assert(pal);

            if (!stream)
                throw Commons::IOException("Stream is not opened");

            // TODO
        }
    }
}