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

        class ActorStartChunk : NonObject
        {
        public:
			static const uint32_t MAGIC = ChunkHeader::CHUNK_ACTOR_START;

            static void read(Commons::StreamReader& reader, ActorPtr& actor)
            {
                actor->setFlags(reader.readUInt16());
                actor->setName(reader.readNullTermString());
            }

            static void write(ChunkWriter& writer, const ActorPtr& actor)
            {
                Commons::StreamWriter& streamWriter = writer.getStreamWriter();
                writer.beginChunk(MAGIC);
				streamWriter.writeUInt16(actor->getFlags());
				streamWriter.writeNullTermString(actor->getName());
                writer.endChunk();
            }
        };

        class ActorMatrixChunk : NonObject
        {
        public:
			static const uint32_t MAGIC = ChunkHeader::CHUNK_ACTOR_TRANSFORM_MATRIX;

            static void read(Commons::StreamReader& reader, ActorPtr& actor)
            {
                Matrix34 matrix;
                ReadMatrix34(reader, matrix);
                actor->setTransform(matrix);                
            }

            static void write(ChunkWriter& writer, const ActorPtr& actor)
            {
				// TODO: check if identity
				writer.beginChunk(MAGIC);
				WriteMatrix34(writer.getStreamWriter(), actor->getTransform());
				writer.endChunk();
            }
        };

        class ActorHierarchyStart : NonObject
        {
        public:
			static const uint32_t MAGIC = ChunkHeader::CHUNK_ACTOR_HIERARCHY_START;

            static void read(Commons::StreamReader& reader, ActorPtr& actor)
            {
				// It is called for NOT every chunk with children
				actor->setHierarchyStartFlag(true);
            }

            static void write(ChunkWriter& writer, const ActorPtr& actor)
            {
				if (!actor->getHierarchyStartFlag()) return;
				writer.beginChunk(MAGIC);
				writer.endChunk();
            }
        };

        class ActorHierarchyPop : NonObject
        {
        public:
			static const uint32_t MAGIC = ChunkHeader::CHUNK_ACTOR_HIERARCHY_POP;

            static void write(ChunkWriter& writer)
            {
				writer.beginChunk(MAGIC);
				writer.endChunk();
            }
        };

        class ActorModelChunk : NonObject
        {
        public:
			static const uint32_t MAGIC = ChunkHeader::CHUNK_ACTOR_MODEL_NAME;

            static void read(Commons::StreamReader& reader, ActorPtr& actor)
            {
                actor->setModel(reader.readNullTermString());
            }

            static void write(ChunkWriter& writer, const ActorPtr& actor)
            {
				if (actor->getModel().empty()) return;
				writer.beginChunk(MAGIC);
				writer.getStreamWriter().writeNullTermString(actor->getModel());
				writer.endChunk();
            }
        };

        class ActorEmptyChunk : NonObject
        {
        public:
			static const uint32_t MAGIC = ChunkHeader::CHUNK_ACTOR_UNKNOWN;

            static void write(ChunkWriter& writer, const ActorPtr& actor)
            {
				if (!actor->getUnknownFlag()) return;
				writer.beginChunk(MAGIC);
				writer.endChunk();
            }
        };
          
        class ActorMaterialChunk : NonObject
        {
        public:
			static const uint32_t MAGIC = ChunkHeader::CHUNK_ACTOR_MATERIAL_NAME;

            static void read(Commons::StreamReader& reader, ActorPtr& actor)
            {
                actor->setMaterial(reader.readNullTermString());
            }

            static void write(ChunkWriter& writer, const ActorPtr& actor)
            {
				if (actor->getMaterial().empty()) return;
				writer.beginChunk(MAGIC);
				writer.getStreamWriter().writeNullTermString(actor->getMaterial());
				writer.endChunk();
            }
        };

        class ActorBBoxChunk : NonObject
        {
        public:
			static const uint32_t MAGIC = ChunkHeader::CHUNK_ACTOR_BOUNDING_BOX;

            static void read(Commons::StreamReader& reader, ActorPtr& actor)
            {
                BBox box;
                ReadBBox(reader, box);
                actor->setBbox(box);
            }

            static void write(ChunkWriter& writer, const ActorPtr& actor)
            {
				if (actor->getBbox().empty()) return;
				writer.beginChunk(MAGIC);
				WriteBBox(writer.getStreamWriter(), actor->getBbox());
				writer.endChunk();
            }
        };

        ActorSerializer::ActorSerializer()
            : ChunkReader()
			, mActorRoots()
			, mActorsStack()
            , mCurActor()
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
			case ActorStartChunk::MAGIC:
			{
				mCurActor.reset(new Actor());
				if (mActorsStack.empty())
				{
					mActorRoots.push_back(mCurActor);
				}
				else
				{
					ActorPtr parent = mActorsStack.top();
					mCurActor->setParent(parent);
					parent->addChild(mCurActor);
				}
				mActorsStack.push(mCurActor);
				ActorStartChunk::read(reader, mCurActor);
				break;
			}
			case ActorMatrixChunk::MAGIC:
				checkCurActor();
				ActorMatrixChunk::read(reader, mCurActor);
				break;
			case ActorHierarchyStart::MAGIC:
				checkCurActor();
				ActorHierarchyStart::read(reader, mCurActor);
				break;
			case ActorHierarchyPop::MAGIC:
				if (mActorsStack.empty()) throw SerializationException("Actor hierarchy pop violation");
				mActorsStack.pop();
				break;
			case ActorMaterialChunk::MAGIC:
				checkCurActor();
				ActorMaterialChunk::read(reader, mCurActor);
				break;
			case ActorModelChunk::MAGIC:
				checkCurActor();
				ActorModelChunk::read(reader, mCurActor);
				break;
			case ActorEmptyChunk::MAGIC:
				checkCurActor();
				// It is called for every actor. TODO: flag not needed?
				mCurActor->setUnknownFlag(true);
				break;
			case ActorBBoxChunk::MAGIC:
				checkCurActor();
				ActorBBoxChunk::read(reader, mCurActor);
				break;
            case ChunkHeader::CHUNK_NULL:
				if (mActorsStack.size() != 1) throw SerializationException(StringUtils::FormatString("Hierarchy level mismatch: %d", mActorsStack.size()));
				checkCurActor();
                mReadCallback(mActorsStack.top());
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

		void ActorSerializer::writeActor(ChunkWriter& writer, const ActorPtr actor)
		{
			ActorStartChunk::write(writer, actor);
			ActorMatrixChunk::write(writer, actor);
			ActorEmptyChunk::write(writer, actor);
			ActorModelChunk::write(writer, actor);
			ActorMaterialChunk::write(writer, actor);
			ActorBBoxChunk::write(writer, actor);
			const auto children = actor->getChildren();
			if (!children.empty())
			{
				ActorHierarchyStart::write(writer, mCurActor);
				
				auto it = children.begin();
				const auto itEnd = children.end();
				while (it != itEnd)
				{
					writeActor(writer, *it);
					++it;
				}
				ActorHierarchyPop::write(writer);
			}
		}

        void ActorSerializer::write(const Commons::IOStreamPtr& stream, TWriteCallback callback)
        {
            assert(stream);
            assert(callback);

            FileHeader header;
            ChunkWriter writer(stream, header);
           
			while (const ActorPtr actor = callback())
            {
				writeActor(writer, actor);
			}
			writer.writeNullChunk();
            writer.finish();
        }
    }
}
