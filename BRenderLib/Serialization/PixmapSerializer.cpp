#include <Serialization/PixmapSerializer.h>
#include <Common/StringUtils.h>
#include <Serialization/ChunkWriter.h>
#include <Streams/StreamReader.h>
#include <Exception/Exception.h>
#include <cassert>

using namespace Commons;

namespace OpenCarma
{
    namespace BRender
    {
        class TextureHeadChunk : NonObject
        {
        public:
			static const uint32_t MAGIC = ChunkHeader::CHUNK_TEXTURE_HEAD;

            static void read(StreamReader& reader, PixmapPtr& pixmap)
            {
                uint8_t pixelFormat = reader.readUInt8();
                int16_t stride = reader.readUInt16();
                uint16_t width = reader.readUInt16();
                uint16_t height = reader.readUInt16();
                int16_t offsetX = reader.readUInt16();
                int16_t offsetY = reader.readUInt16();
                std::string name = reader.readNullTermString();

                Pixmap::PixelFormat pixFormat = static_cast<Pixmap::PixelFormat>(pixelFormat);
                if (pixFormat >= Pixmap::BR_PMT_MAX)
                    throw SerializationException(StringUtils::FormatString("Unknown pixel format: %d", pixFormat));
                pixmap.reset(new Pixmap(pixFormat, width, height, stride));
                pixmap->setXOffset(offsetX);
                pixmap->setYOffset(offsetY);
                pixmap->setName(name);
            }

            static void write(ChunkWriter& writer, const Pixmap& pixmap)
            {
                writer.beginChunk(MAGIC);
                StreamWriter& streamWriter = writer.getStreamWriter();
                streamWriter.writeUInt8(static_cast<uint8_t>(pixmap.getPixelFormat()));
                streamWriter.writeUInt16(pixmap.getStride());
                streamWriter.writeUInt16(pixmap.getWidth());
                streamWriter.writeUInt16(pixmap.getHeight());
                streamWriter.writeUInt16(pixmap.getXOffset());
                streamWriter.writeUInt16(pixmap.getYOffset());
                streamWriter.writeNullTermString(pixmap.getName());
                writer.endChunk();
            }
        };

        class TextureDataChunk : NonObject
        {
        public:
			static const uint32_t MAGIC = ChunkHeader::CHUNK_TEXTURE_DATA;

            static void read(StreamReader& reader, PixmapPtr& pixmap)
            {
                uint32_t numPixels = reader.readUInt32();
                uint32_t bpp = reader.readUInt32();
                uint32_t size = bpp * numPixels;
                if (pixmap->getBpp() != bpp)
                    throw SerializationException(StringUtils::FormatString("Bpp mismatch: need %d, got %d", pixmap->getBpp(), bpp));

                if (pixmap->getRawSize() != size)
                    throw SerializationException(StringUtils::FormatString("Raw size mismatch: need %d, got %d", pixmap->getRawSize(), size));

                reader.read(pixmap->getRawBuf(), size);
            }

            static void write(ChunkWriter& writer, const Pixmap& pixmap)
            {
                writer.beginChunk(MAGIC);
                StreamWriter& streamWriter = writer.getStreamWriter();
                uint32_t bpp = pixmap.getBpp();
                uint32_t numPixels = pixmap.getRawSize() / bpp;
                streamWriter.writeUInt32(numPixels);
                streamWriter.writeUInt32(bpp);
                streamWriter.write(pixmap.getRawBufConst(), pixmap.getRawSize());
                writer.endChunk();
            }
        };

        PixmapSerializer::PixmapSerializer()
            : ChunkReader()
            , mCurPixmap()
            , mHasHeaderChunk(false)
            , mHasDataChunk(false)
            , mReadCallback()
        {
        }

        bool PixmapSerializer::onChunkRead(const ChunkHeader& header, StreamReader& reader)
		{
			switch (header.getMagic())
			{
			case TextureHeadChunk::MAGIC:
                TextureHeadChunk::read(reader, mCurPixmap);
                mHasHeaderChunk = true;
				break;
			case TextureDataChunk::MAGIC:
                if (!mHasHeaderChunk)
                    throw SerializationException(StringUtils::FormatString("CHUNK_TEXTURE_DATA before CHUNK_TEXTURE_HEAD at %d", reader.tell()));
                TextureDataChunk::read(reader, mCurPixmap);
                mHasDataChunk = true;
				break;
            case ChunkHeader::CHUNK_NULL:
                if (!mHasHeaderChunk || !mHasDataChunk)
                    throw SerializationException("Pixelmap object is empty, but null chunk is found");
                mReadCallback(mCurPixmap);
                mCurPixmap.reset();
                mHasDataChunk = false;
                mHasHeaderChunk = false;
				break;
            default:
                return false;
			}
            return true;
		}

        void PixmapSerializer::read(const IOStreamPtr& stream, TReadCallback callback)
        {
            assert(stream);
            assert(callback);

            mReadCallback = callback;
			doRead(stream);
        }

        void PixmapSerializer::write(const IOStreamPtr& stream, TWriteCallback callback)
        {
            assert(stream);
            assert(callback);

            FileHeader header;
            ChunkWriter writer(stream, header);
            while (const PixmapPtr pixmap = callback())
            {
                TextureHeadChunk::write(writer, *pixmap);
                TextureDataChunk::write(writer, *pixmap);
                writer.writeNullChunk();
            }                        
            writer.finish();
        }
    }
}