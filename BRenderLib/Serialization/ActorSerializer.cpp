#include <Serialization/ChunkWriter.h>
#include <Serialization/ActorSerializer.h>
#include <Streams/StreamReader.h>
#include <Common/StringUtils.h>
#include <Exception/Exception.h>
#include <Logger/Log.h>
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
                //WriteBBox(writer.getStreamWriter(), actor->getBbox());
            }
        };


        ActorSerializer::ActorSerializer()
            : ChunkReader()
            , mCurActor()
			, mCurLevel(0)
            , mReadCallback()
        {
        }

		void ActorSerializer::checkCurActor()
		{
			if (!mCurActor) throw SerializationException("Current actor is null");
		}

        bool ActorSerializer::onChunkRead(const ChunkHeader& header, Commons::StreamReader& reader)
        {
            switch (header.getMagic())
            {
            case ChunkHeader::CHUNK_ACTOR_NAME:
			{
				ActorPtr parent = mCurActor;
				mCurActor.reset(new Actor());
				if (parent)
				{
					parent->addChild(mCurActor);
					mCurActor->setParent(parent);
				}
				else
				{
					// TODO: check if can be multiple roots
					mRootActor = mCurActor;
				}
				ActorNameChunk::read(reader, mCurActor);
				LOG_DEBUG("Actor name: %s", mCurActor->getName().c_str());
				++mCurLevel;
				break;
			}
			case ChunkHeader::CHUNK_ACTOR_TRANSFORM_MATRIX:
				checkCurActor();
				ActorMatrixChunk::read(reader, mCurActor);
				LOG_DEBUG("Actor matrix");
				break;
			case ChunkHeader::CHUNK_ACTOR_HIERARCHY_BEGIN:
				LOG_DEBUG("Actor push");
				// TODO: push/pull
				//++mCurLevel;
				break;
			case ChunkHeader::CHUNK_ACTOR_HIERARCHY_END:
				LOG_DEBUG("Actor pop");
				--mCurLevel;
				mCurActor = mCurActor->getParent().lock();
				// TODO: check lvl match
				break;
			case ChunkHeader::CHUNK_ACTOR_MATERIAL_NAMES:
				checkCurActor();
				ActorMaterialChunk::read(reader, mCurActor); // TODO: multiple materials?
				LOG_DEBUG("Material names");
				break;
			case ChunkHeader::CHUNK_ACTOR_MODEL_NAME:
				checkCurActor();
				ActorModelChunk::read(reader, mCurActor);
				LOG_DEBUG("Model: %s", mCurActor->getModel().c_str());
				break;
			case ChunkHeader::CHUNK_ACTOR_UNKNOWN:
				LOG_DEBUG("Unk");
				// TODO: log
				break;
			case ChunkHeader::CHUNK_ACTOR_BOUNDING_BOX:
				checkCurActor();
				ActorBBoxChunk::read(reader, mCurActor);
				LOG_DEBUG("BBox");
				break;
            case ChunkHeader::CHUNK_NULL:
				if (mCurLevel != 1) throw SerializationException(StringUtils::FormatString("Hierarchy level mismatch: %d", mCurLevel));					
				checkCurActor();
                mReadCallback(mCurActor); // TODO: single root callback?				
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
