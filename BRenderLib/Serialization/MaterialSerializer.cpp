#include <Serialization/ChunkWriter.h>
#include <Serialization/MaterialSerializer.h>
#include <Streams/StreamReader.h>
#include <Exception/Exception.h>
#include <cassert>

using namespace Commons;

namespace OpenCarma
{
    namespace BRender
    {
        static void ReadMatrix23(Commons::StreamReader& reader, Matrix23& matrix)
        {
            for (uint32_t i = 0; i < 6; ++i)
                matrix.mValue[i] = reader.readFloat();
        }

        static void WriteMatrix23(Commons::StreamWriter& writer, const Matrix23& matrix)
        {
            for (uint32_t i = 0; i < 6; ++i)
                writer.writeFloat(matrix.mValue[i]);
        }

        class MaterialAttributesV1Chunk : NonObject
        {
        public:
            static void read(Commons::StreamReader& reader, MaterialPtr& material)
            {
                material->setColor(Color(reader.readUInt32()));
                material->setAmbient(reader.readFloat());
                material->setDiffuse(reader.readFloat());
                material->setSpecular(reader.readFloat());
                material->setSpecularPower(reader.readFloat());
                material->setIndexedColor(reader.readUInt8(), reader.readUInt8());
                material->setFlags(reader.readUInt32());
                Matrix23 matrix;
                ReadMatrix23(reader, matrix);
                material->setTransform(matrix);
                material->setName(reader.readNullTermString());
            }

            static void write(ChunkWriter& writer, const MaterialPtr& material)
            {
                Commons::StreamWriter& streamWriter = writer.getStreamWriter();
                writer.beginChunk(ChunkHeader::CHUNK_MATERIAL_ATTRIBUTES_V1);
                streamWriter.writeUInt32(material->getColor().mValue);
                streamWriter.writeFloat(material->getAmbient());
                streamWriter.writeFloat(material->getDiffuse());
                streamWriter.writeFloat(material->getSpecular());
                streamWriter.writeFloat(material->getSpecularPower());
                streamWriter.writeUInt8(material->getIndexedBase());
                streamWriter.writeUInt8(material->getIndexedRange());
                streamWriter.writeUInt32(material->getFlags());
                WriteMatrix23(streamWriter, material->getTransform());
                streamWriter.writeNullTermString(material->getName());
                writer.endChunk();
            }
        };

        // TODO: check if used
        class MaterialAttributesV2Chunk : NonObject
        {
        public:
            static void read(Commons::StreamReader& reader, MaterialPtr& material)
            {
                material->setColor(Color(reader.readUInt32()));
                material->setAmbient(reader.readFloat());
                material->setDiffuse(reader.readFloat());
                material->setSpecular(reader.readFloat());
                material->setSpecularPower(reader.readFloat());
                material->setFlags(reader.readUInt32());
                Matrix23 matrix;
                ReadMatrix23(reader, matrix);
                material->setTransform(matrix);
                reader.seek(17, IOStream::ORIGIN_CUR);
                material->setName(reader.readNullTermString());
            }
            
            // Not writing this chunk, using V1 instead 
        };

        class MaterialPixmapNameChunk : NonObject
        {
        public:
            static void read(Commons::StreamReader& reader, const MaterialPtr& material)
            {
                std::string value = reader.readNullTermString();
                material->setPixmap(value);
            }

            static void write(ChunkWriter& writer, const MaterialPtr& material)
            {
                if (!material->getPixmap().empty()) return;
                writer.beginChunk(ChunkHeader::CHUNK_MATERIAL_PIXELMAP_NAME);
                writer.getStreamWriter().writeNullTermString(material->getPixmap());
                writer.endChunk();
            }
        };

        class MaterialShadetabNameChunk : NonObject
        {
        public:
            static void read(Commons::StreamReader& reader, const MaterialPtr& material)
            {
                std::string value = reader.readNullTermString();
                material->setShadetab(value);
            }

            static void write(ChunkWriter& writer, const MaterialPtr& material)
            {
                if (!material->getShadetab().empty())
                writer.beginChunk(ChunkHeader::CHUNK_MATERIAL_SHADETAB_NAME);
                writer.getStreamWriter().writeNullTermString(material->getShadetab());
                writer.endChunk();
            }
        };

        MaterialSerializer::MaterialSerializer()
            : ChunkReader()
            , mCurMaterial()
            , mReadCallback()
        {
        }

        void MaterialSerializer::checkCurMat()
        {
            if (!mCurMaterial) throw SerializationException("Current material is null");
        }

        bool MaterialSerializer::onChunkRead(const ChunkHeader& header, Commons::StreamReader& reader)
        {
            switch (header.getMagic())
            {
            case ChunkHeader::CHUNK_MATERIAL_ATTRIBUTES_V1:
                mCurMaterial.reset(new Material());
                MaterialAttributesV1Chunk::read(reader, mCurMaterial);
                break;
            case ChunkHeader::CHUNK_MATERIAL_ATTRIBUTES_V2:
                throw SerializationException("CHUNK_MATERIAL_ATTRIBUTES_V2 not implemented");
                break;
            case ChunkHeader::CHUNK_MATERIAL_PIXELMAP_NAME:
                checkCurMat();
                MaterialPixmapNameChunk::read(reader, mCurMaterial);
                break;
            case ChunkHeader::CHUNK_MATERIAL_SHADETAB_NAME:
                checkCurMat();
                MaterialShadetabNameChunk::read(reader, mCurMaterial);
                break;
            case ChunkHeader::CHUNK_NULL:
                checkCurMat();
                mReadCallback(mCurMaterial);
                mCurMaterial.reset();
                break;
            default:
                return false;
            }
            return true;
        }

        void MaterialSerializer::read(const Commons::IOStreamPtr& stream, TReadCallback callback)
        {
            assert(stream);
            assert(callback);

            mReadCallback = callback;
            doRead(stream);
        }

        void MaterialSerializer::write(const Commons::IOStreamPtr& stream, TWriteCallback callback)
        {
            assert(stream);
            assert(callback);

            FileHeader header;
            ChunkWriter writer(stream, header);
            while (const MaterialPtr material = callback())
            {
                MaterialAttributesV1Chunk::write(writer, material);
                MaterialPixmapNameChunk::write(writer, material);
                MaterialShadetabNameChunk::write(writer, material);
                writer.writeNullChunk();
            }
            writer.finish();
        }
    }
}