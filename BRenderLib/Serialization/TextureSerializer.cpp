#include <cassert>
#include <sstream>
#include <Serialization/TextureSerializer.h>
#include <BigEndianStreamReader.h>
#include <Exception.h>

namespace OpenCarma
{
    namespace BRender
    {
        void TextureSerializer::DeserializePixelmap(std::istream& stream, std::vector<PixmapPtr>& pixelmaps)
        {
            if (!stream)
                throw IOException("Stream is not opened");

            PixmapPtr curPixmap;

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
                        throw SerializationException("Pixelmap object is incorrect");
                    pixelmaps.push_back(curPixmap);
                    curPixmap.reset();
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
        }

        void TextureSerializer::SerializePixelmap(const PixmapPtr& pal, std::ostream& stream)
        {
            assert(pal);

            if (!stream)
                throw IOException("Stream is not opened");

            // TODO
        }

        //PixmapPtr TextureSerializer::DeserializePixmap(Stream& stream)
        //{
        //    PixmapPtr pixmap(new Pixmap());

        //    BigEndianStreamReader reader(stream);

        //    ChunkHeader header;
        //    while (true)
        //    {
        //        header.setMagic(reader.readUInt32());
        //        header.setSize(reader.readUInt32());

        //        // EOF
        //        if (reader.isEOF())
        //            break;

        //        if (header.getMagic() == CHUNK_HEADER)
        //        {
        //            FileHeaderChunk fileHeader;
        //            fileHeader.read(header, reader);
        //        }
        //        else if (header.getMagic() == CHUNK_TEXTURE_HEAD)
        //        {
        //            TextureHeadChunk headChunk;
        //            headChunk.ReadFromStream(header, reader);

        //            pixmap->m_header = headChunk;
        //        }
        //        else if (header.getMagic() == CHUNK_TEXTURE_DATA)
        //        {
        //            uint32_t numData = reader.readUInt32();
        //            uint32_t sizeData = reader.readUInt32();

        //            // TODO: validators
        //            assert(numData * sizeData == pixmap->getWidth() * pixmap->getHeight());

        //            pixmap->m_pixels.resize(numData * sizeData);
        //            reader.read(&pixmap->m_pixels[0], numData * sizeData);
        //        }
        //        else if (header.getMagic() == CHUNK_NULL)
        //        {
        //            // Do nothing...
        //        }
        //        else
        //        {
        //            throw SerializationException("Unknown chunk");
        //        }
        //    }

        //    // TODO: check available data; construct

        //    return pixmap;
        //}


        //MaterialPtr TextureSerializer::DeserializeMaterial(Stream& stream)
        //{
        //    MaterialPtr material(new Material());

        //    BigEndianStreamReader reader(stream);

        //    ChunkHeader header;
        //    while (true)
        //    {
        //        header.setMagic(reader.readUInt32());
        //        header.setSize(reader.readUInt32());

        //        // EOF
        //        if (reader.isEOF())
        //            break;

        //        if (header.getMagic() == CHUNK_HEADER)
        //        {
        //            FileHeaderChunk fileHeader;
        //            fileHeader.read(header, reader);
        //        }
        //        else if (header.getMagic() == CHUNK_MATERIAL_ATTRIBUTES_V1)
        //        {
        //            MaterialAttributesV1Chunk headChunk;
        //            headChunk.ReadFromStream(header, reader);

        //            material->m_header = headChunk;
        //        }
        //        else if (header.getMagic() == CHUNK_PIXELMAP_NAME)
        //        {
        //            material->m_pixelmapName = reader.readString();
        //            // TODO: validators
        //        }
        //        else if (header.getMagic() == CHUNK_SHADETAB_NAME)
        //        {
        //            material->m_shadetabName = reader.readString();
        //            // TODO: validators
        //        }
        //        else if (header.getMagic() == CHUNK_NULL)
        //        {
        //            // Do nothing...
        //        }
        //        else
        //        {
        //            throw SerializationException("Unknown chunk");
        //        }
        //    }

        //    // TODO: check available data; construct

        //    return material;
        //}

        //ActorPtr TextureSerializer::DeserializeActor(Stream& stream)
        //{
        //    ActorPtr actor(new Actor());

        //    BigEndianStreamReader reader(stream);

        //    ChunkHeader header;
        //    while (true)
        //    {
        //        header.setMagic(reader.readUInt32());
        //        header.setSize(reader.readUInt32());

        //        // EOF
        //        if (reader.isEOF())
        //            break;

        //        if (header.getMagic() == CHUNK_HEADER)
        //        {
        //            FileHeaderChunk fileHeader;
        //            fileHeader.read(header, reader);
        //        }
        //        else if (header.getMagic() == CHUNK_ACTOR_NAME)
        //        {
        //            ActorStartChunk startChunk;
        //            startChunk.ReadFromStream(header, reader);

        //            // TODO
        //            //actor = headChunk;
        //        }
        //        else if (header.getMagic() == CHUNK_ACTOR_TRANSFORM_MATRIX)
        //        {
        //            TransformMatrixChunk transformChunk;
        //            transformChunk.ReadFromStream(header, reader);

        //            int k = 0;
        //            // TODO
        //            //actor = headChunk;
        //        }
        //        else if (header.getMagic() == CHUNK_ACTOR_HIERARCHY_BEGIN)
        //        {
        //            HierarchyBeginChunk beginChunk;
        //            beginChunk.ReadFromStream(header, reader);
        //        }
        //        else if (header.getMagic() == CHUNK_ACTOR_HIERARCHY_END)
        //        {
        //            HierarchyBeginChunk beginChunk;
        //            beginChunk.ReadFromStream(header, reader);
        //        }
        //        else if (header.getMagic() == CHUNK_ACTOR_UNKNOWN)
        //        {
        //            // Unknown; empty...
        //        }
        //        else if (header.getMagic() == CHUNK_ACTOR_BOUNDING_BOX)
        //        {
        //            BBoxChunk bboxChunk;
        //            bboxChunk.ReadFromStream(header, reader);
        //        }
        //        else if (header.getMagic() == CHUNK_ACTOR_MATERIAL_NAMES)
        //        {
        //            MaterialNamesChunk namesChunk;
        //            namesChunk.ReadFromStream(header, reader);
        //        }
        //        else if (header.getMagic() == CHUNK_NULL)
        //        {
        //            // Do nothing...
        //        }
        //        else
        //        {
        //            throw SerializationException("Unknown chunk");
        //        }
        //    }

        //    // TODO: check available data; construct

        //    return actor;
        //}
    }
}