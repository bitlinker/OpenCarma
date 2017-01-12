#include <cassert>
#include <sstream>
#include <Serialization/ActorSerializer.h>
#include <EndianStreamReader.h>
#include <Exception/Exception.h>

namespace OpenCarma
{
    namespace BRender
    {
        // TODO: my streams
        void ActorSerializer::DeserializeActor(std::istream& stream, std::vector<ActorPtr>& actors)
        {
            if (!stream)
                throw Commons::IOException("Stream is not opened");

            ActorPtr curActor;
            int32_t curLevel = 0;

            EndianStreamReader reader(stream);

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
                else if (header.getMagic() == ActorNameChunk::MAGIC)
                {
                    curActor = ActorPtr(new Actor());
                    assert(curActor.get());
                    curActor->m_header.read(reader);

                    ++curLevel;
                    printf("%d: %s\n", curLevel, curActor->m_header.m_name.data());
                }
                else if (header.getMagic() == ActorMatrixChunk::MAGIC)
                {
                    assert(curActor.get());
                    curActor->m_matrix.read(reader);
                }
                else if (header.getMagic() == ActorPushChunk::MAGIC)
                {
                    assert(curActor.get());
                    // TODO: push
                }
                else if (header.getMagic() == ActorPopChunk::MAGIC)
                {
                    assert(curActor.get());
                    // TODO: pop
                    --curLevel;
                }
                else if (header.getMagic() == ActorMaterialChunk::MAGIC)
                {
                    assert(curActor.get());
                    curActor->m_materials.read(reader);
                }
                else if (header.getMagic() == ActorModelChunk::MAGIC)
                {
                    assert(curActor.get());
                    curActor->m_models.read(reader);
                }
                else if (header.getMagic() == ActorEmptyChunk::MAGIC)
                {
                    assert(curActor.get());
                    curActor->m_empty.read(reader);
                }
                else if (header.getMagic() == ActorBBoxChunk::MAGIC)
                {
                    assert(curActor.get());
                    curActor->m_bbox.read(reader);
                }
                else if (header.isNULL())
                {
                    if (!curActor.get() || !curActor->isValid())
                        throw Commons::SerializationException("Actor object is incorrect");
                    actors.push_back(curActor);
                    curActor.reset();
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
                    //throw SerializationException(ss.str()); // TODO: warning
                    //printf("%s\n", ss.str().data());
                }
            }
        }

        void ActorSerializer::SerializeActor(const ActorPtr& actor, std::ostream& stream)
        {
            assert(actor);

            if (!stream)
                throw Commons::IOException("Stream is not opened");

            // TODO
        }
    }
}