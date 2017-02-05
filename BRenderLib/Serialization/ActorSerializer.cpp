#include <Serialization/ChunkWriter.h>
#include <Serialization/ActorSerializer.h>
#include <Streams/StreamReader.h>
#include <Exception/Exception.h>
#include <cassert>

using namespace Commons;

namespace OpenCarma
{
    namespace BRender
    {
        static void ReadMatrix34(Commons::StreamReader& reader, Matrix34& matrix)
        {
            for (uint32_t i = 0; i < 12; ++i)
                matrix.mValue[i] = reader.readFloat();
        }

        static void WriteMatrix34(Commons::StreamWriter& writer, const Matrix34& matrix)
        {
            for (uint32_t i = 0; i < 12; ++i)
                writer.writeFloat(matrix.mValue[i]);
        }

        static void ReadBBox(Commons::StreamReader& reader, BBox& box)
        {
            for (uint32_t i = 0; i < 3; ++i)
                box.mPos[i] = reader.readFloat();
            for (uint32_t i = 0; i < 3; ++i)
                box.mSize[i] = reader.readFloat();
        }

        static void WriteBBox(Commons::StreamWriter& writer, const BBox& box)
        {
            for (uint32_t i = 0; i < 3; ++i)
                writer.writeFloat(box.mPos[i]);
            for (uint32_t i = 0; i < 3; ++i)
                writer.writeFloat(box.mSize[i]);
        }

        class ActorNameChunk : NonObject
        {
        public:
            static void read(Commons::StreamReader& reader, ActorPtr& actor)
            {
                actor->setFlags(reader.readUInt16());
                actor->setName(reader.readNullTermString());
            }

            static void write(ChunkWriter& writer, const ActorPtr& actor)
            {
                //Commons::StreamWriter& streamWriter = writer.getStreamWriter();
                //        writer.beginChunk(ChunkHeader::CHUNK_MATERIAL_ATTRIBUTES_V1);
                //        streamWriter.writeUInt32(material->getColor().mValue);
                //        streamWriter.writeFloat(material->getAmbient());
                //        streamWriter.writeFloat(material->getDiffuse());
                //        streamWriter.writeFloat(material->getSpecular());
                //        streamWriter.writeFloat(material->getSpecularPower());
                //        streamWriter.writeUInt8(material->getIndexedBase());
                //        streamWriter.writeUInt8(material->getIndexedRange());
                //        streamWriter.writeUInt32(material->getFlags());
                //        WriteMatrix23(streamWriter, material->getTransform());
                //        streamWriter.writeNullTermString(material->getName());
                //        writer.endChunk();
            }
        };

        class ActorMatrixChunk : NonObject
        {
        public:
            static void read(Commons::StreamReader& reader, ActorPtr& actor)
            {
                Matrix34 matrix;
                ReadMatrix34(reader, matrix);
                actor->setTransform(matrix);                
            }

            static void write(ChunkWriter& writer, const ActorPtr& actor)
            {
            }
        };

        class ActorPushChunk : NonObject
        {
        public:
            static void read(Commons::StreamReader& reader, ActorPtr& actor)
            {
            }

            static void write(ChunkWriter& writer, const ActorPtr& actor)
            {
            }
        };

        class ActorPopChunk : NonObject
        {
        public:
            static void read(Commons::StreamReader& reader, ActorPtr& actor)
            {
            }

            static void write(ChunkWriter& writer, const ActorPtr& actor)
            {
            }
        };

        class ActorModelChunk : NonObject
        {
        public:
            static void read(Commons::StreamReader& reader, ActorPtr& actor)
            {
                actor->setModel(reader.readNullTermString());
            }

            static void write(ChunkWriter& writer, const ActorPtr& actor)
            {
            }
        };

        class ActorEmptyChunk : NonObject
        {
        public:
            static void read(Commons::StreamReader& reader, ActorPtr& actor)
            {
            }

            static void write(ChunkWriter& writer, const ActorPtr& actor)
            {
            }
        };
          
        class ActorMaterialChunk : NonObject
        {
        public:
            static void read(Commons::StreamReader& reader, ActorPtr& actor)
            {
                actor->setMaterial(reader.readNullTermString());
            }

            static void write(ChunkWriter& writer, const ActorPtr& actor)
            {
            }
        };

        class ActorBBoxChunk : NonObject
        {
        public:
            static void read(Commons::StreamReader& reader, ActorPtr& actor)
            {
                BBox box;
                ReadBBox(reader, box);
                actor->setBbox(box);
            }

            static void write(ChunkWriter& writer, const ActorPtr& actor)
            {
                // TODO: header
                // TODO: check if has?
                WriteBBox(writer.getStreamWriter(), actor->getBbox());
            }
        };


        ActorSerializer::ActorSerializer()
            : ChunkReader()
            , mCurActor()
            , mReadCallback()
        {
        }

        bool ActorSerializer::onChunkRead(const ChunkHeader& header, Commons::StreamReader& reader)
        {
            switch (header.getMagic())
            {
            case ChunkHeader::CHUNK_ACTOR_NAME:
                mCurActor.reset(new Actor());
                ActorNameChunk::read(reader, mCurActor);
                break;
           
            case ChunkHeader::CHUNK_NULL:
                //checkCurMat();
                mReadCallback(mCurActor);
                mCurActor.reset();
                break;
            default:
                return false;
            }
            return true;
        }

        void ActorSerializer::read(const Commons::IOStreamPtr& stream, TReadCallback callback)
        {
            assert(stream);
            assert(callback);

            mReadCallback = callback;
            doRead(stream);
        }

        void ActorSerializer::write(const Commons::IOStreamPtr& stream, TWriteCallback callback)
        {
            assert(stream);
            assert(callback);

            FileHeader header;
            ChunkWriter writer(stream, header);
            // TODO
           /* while (const MaterialPtr material = callback())
            {
                MaterialAttributesV1Chunk::write(writer, material);
                MaterialPixmapNameChunk::write(writer, material);
                MaterialShadetabNameChunk::write(writer, material);
                writer.writeNullChunk();
            }*/
            writer.finish();
        }
    }
}

//        // TODO: my streams
//        void ActorSerializer::DeserializeActor(std::istream& stream, std::vector<ActorPtr>& actors)
//        {
//            if (!stream)
//                throw Commons::IOException("Stream is not opened");
//
//            ActorPtr curActor;
//            int32_t curLevel = 0;
//
//            EndianStreamReader reader(stream, Commons::Endianness::BIG_ENDIAN);
//
//            FileHeaderChunk fileHeader;
//            ChunkHeader header;
//            while (!reader.isEOF())
//            {
//                header.read(reader);
//
//                uint32_t lastOffset = reader.tell();
//
//                if (header.getMagic() == FileHeaderChunk::MAGIC)
//                {
//                    fileHeader.read(reader);                    
//                }
//                else if (header.getMagic() == ActorNameChunk::MAGIC)
//                {
//                    curActor = ActorPtr(new Actor());
//                    assert(curActor.get());
//                    curActor->m_header.read(reader);
//
//                    ++curLevel;
//                    printf("%d: %s\n", curLevel, curActor->m_header.m_name.data());
//                }
//                else if (header.getMagic() == ActorMatrixChunk::MAGIC)
//                {
//                    assert(curActor.get());
//                    curActor->m_matrix.read(reader);
//                }
//                else if (header.getMagic() == ActorPushChunk::MAGIC)
//                {
//                    assert(curActor.get());
//                    // TODO: push
//                }
//                else if (header.getMagic() == ActorPopChunk::MAGIC)
//                {
//                    assert(curActor.get());
//                    // TODO: pop
//                    --curLevel;
//                }
//                else if (header.getMagic() == ActorMaterialChunk::MAGIC)
//                {
//                    assert(curActor.get());
//                    curActor->m_materials.read(reader);
//                }
//                else if (header.getMagic() == ActorModelChunk::MAGIC)
//                {
//                    assert(curActor.get());
//                    curActor->m_models.read(reader);
//                }
//                else if (header.getMagic() == ActorEmptyChunk::MAGIC)
//                {
//                    assert(curActor.get());
//                    curActor->m_empty.read(reader);
//                }
//                else if (header.getMagic() == ActorBBoxChunk::MAGIC)
//                {
//                    assert(curActor.get());
//                    curActor->m_bbox.read(reader);
//                }
//                else if (header.isNULL())
//                {
//                    if (!curActor.get() || !curActor->isValid())
//                        throw Commons::SerializationException("Actor object is incorrect");
//                    actors.push_back(curActor);
//                    curActor.reset();
//                }
//                else

//        }
//
//        void ActorSerializer::SerializeActor(const ActorPtr& actor, std::ostream& stream)
//        {
//            assert(actor);
//
//            if (!stream)
//                throw Commons::IOException("Stream is not opened");
//
//            // TODO
//        }
//    }
//}