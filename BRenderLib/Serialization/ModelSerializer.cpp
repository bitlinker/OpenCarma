#include <Serialization/ModelSerializer.h>
#include <Serialization/ChunkWriter.h>
#include <Exception/Exception.h>
#include <Streams/StreamReader.h>
#include <algorithm>
#include <cassert>

using namespace Commons;

namespace OpenCarma
{
    namespace BRender
    {
        class ModelHeadChunk : NonObject
        {
            // TODO: move chunk constant here?
        public:
            static void read(StreamReader& reader, ModelPtr& model)
            {
                model.reset(new Model());
                uint16_t unk = reader.readUInt16();
                model->setName(reader.readNullTermString());
            }

            static void write(ChunkWriter& writer, const ModelPtr& model)
            {
                writer.beginChunk(ChunkHeader::CHUNK_MODEL_HEAD);
                StreamWriter& streamWriter = writer.getStreamWriter();
                streamWriter.writeUInt16(0); // TODO needed?
                streamWriter.writeNullTermString(model->getName());
                writer.endChunk();
            }
        };

        class ModelVerticesChunk : NonObject
        {
        public:
            static void read(StreamReader& reader, ModelPtr& model)
            {
                uint32_t count = reader.readUInt32();
                std::vector<Model::Vertex3f>& vertices = model->getVertices();
                vertices.resize(count);
                std::for_each(vertices.begin(), vertices.end(), [&reader](Model::Vertex3f& vertex) {
                    for (uint32_t k = 0; k < 3; ++k)
                        vertex.mValue[k] = reader.readFloat();
                });
            }

            static void write(ChunkWriter& writer, const ModelPtr& model)
            {
                const std::vector<Model::Vertex3f>& vertices = model->getVertices();
                if (vertices.empty()) return;
                writer.beginChunk(ChunkHeader::CHUNK_MODEL_VERTICES);
                StreamWriter& streamWriter = writer.getStreamWriter();                
                streamWriter.writeUInt32(vertices.size());
                std::for_each(vertices.begin(), vertices.end(), [&streamWriter](const Model::Vertex3f& vertex) {
                    for (uint32_t k = 0; k < 3; ++k)
                        streamWriter.writeFloat(vertex.mValue[k]);
                });                
                writer.endChunk();
            }
        };

        class ModelUVsChunk : NonObject
        {
        public:
            static void read(StreamReader& reader, ModelPtr& model)
            {
                uint32_t count = reader.readUInt32();
                std::vector<Model::Vertex2f>& uvs = model->getUVs();
                uvs.resize(count);
                std::for_each(uvs.begin(), uvs.end(), [&reader](Model::Vertex2f& uv) {
                    for (uint32_t k = 0; k < 2; ++k)
                        uv.mValue[k] = reader.readFloat();
                });                
            }

            static void write(ChunkWriter& writer, const ModelPtr& model)
            {
                const std::vector<Model::Vertex2f>& uvs = model->getUVs();
                if (uvs.empty()) return;
                writer.beginChunk(ChunkHeader::CHUNK_MODEL_UVS);
                StreamWriter& streamWriter = writer.getStreamWriter();
                streamWriter.writeUInt32(uvs.size());
                std::for_each(uvs.begin(), uvs.end(), [&streamWriter](const Model::Vertex2f& uv) {
                    for (uint32_t k = 0; k < 2; ++k)
                        streamWriter.writeFloat(uv.mValue[k]);
                });
                writer.endChunk();
            }
        };

        class ModelFacesChunk : NonObject
        {
        public:
            static void read(StreamReader& reader, ModelPtr& model)
            {
                uint32_t count = reader.readUInt32();               
                std::vector<Model::Face>& faces = model->getFaces();
                faces.resize(count);
                std::for_each(faces.begin(), faces.end(), [&reader](Model::Face& face) {
                    for (uint32_t k = 0; k < 3; ++k)
                        face.mV[k] = reader.readUInt16();
                    for (uint32_t k = 0; k < 3; ++k)
                        face.mUnknown[k] = reader.readUInt8();
                });                
            }

            static void write(ChunkWriter& writer, const ModelPtr& model)
            {
                const std::vector<Model::Face>& faces = model->getFaces();
                if (faces.empty()) return;
                writer.beginChunk(ChunkHeader::CHUNK_MODEL_FACES);
                StreamWriter& streamWriter = writer.getStreamWriter();
                streamWriter.writeUInt32(faces.size());
                std::for_each(faces.begin(), faces.end(), [&streamWriter](const Model::Face& face) {
                    for (uint32_t k = 0; k < 3; ++k)
                        streamWriter.writeUInt16(face.mV[k]);
                    for (uint32_t k = 0; k < 3; ++k)
                        streamWriter.writeUInt8(face.mUnknown[k]);
                });
                writer.endChunk();
            }            
        };

        class ModelMaterialsChunk : NonObject
        {
        public:
            static void read(StreamReader& reader, ModelPtr& model)
            {
                uint32_t count = reader.readUInt32();
                std::vector<std::string>& materials = model->getMaterials();
                materials.resize(count);
                std::for_each(materials.begin(), materials.end(), [&reader](std::string& mat) {
                    mat = reader.readNullTermString();
                });
            }

            static void write(ChunkWriter& writer, const ModelPtr& model)
            {
                const std::vector<std::string>& materials = model->getMaterials();
                if (materials.empty()) return;
                writer.beginChunk(ChunkHeader::CHUNK_MODEL_MATERIALS);
                StreamWriter& streamWriter = writer.getStreamWriter();
                streamWriter.writeUInt32(materials.size());
                std::for_each(materials.begin(), materials.end(), [&streamWriter](const std::string& mat) {
                    streamWriter.writeNullTermString(mat);
                });
                writer.endChunk();
            }
        };

        class ModelFaceMaterialsChunk : NonObject
        {
        public:
            static void read(StreamReader& reader, ModelPtr& model)
            {
                uint32_t faceMatCount = reader.readUInt32();
                uint32_t bytesPerEntry = reader.readUInt32();
                if (bytesPerEntry != 2) throw Commons::SerializationException("Face material indexes is not 16 bit");
                std::vector<uint16_t>& faceMats = model->getFaceMats();
                faceMats.resize(faceMatCount);
                std::for_each(faceMats.begin(), faceMats.end(), [&reader](uint16_t& index) {
                    index = reader.readUInt16();
                });
            }

            static void write(ChunkWriter& writer, const ModelPtr& model)
            {
                const std::vector<uint16_t>& faceMats = model->getFaceMats();
                if (faceMats.empty()) return;
                writer.beginChunk(ChunkHeader::CHUNK_MODEL_FACE_MATERIALS);
                StreamWriter& streamWriter = writer.getStreamWriter();
                streamWriter.writeUInt32(faceMats.size());
                streamWriter.writeUInt32(2);
                std::for_each(faceMats.begin(), faceMats.end(), [&streamWriter](const uint16_t& index) {
                    streamWriter.writeUInt16(index);
                });
                writer.endChunk();
            }
        };

        ModelSerializer::ModelSerializer()
            : mCurModel()
            , mReadCallback()
        {
        }

        void ModelSerializer::checkCurModel()
        {
            if (!mCurModel) throw SerializationException("Current model is null");
        }

        bool ModelSerializer::onChunkRead(const ChunkHeader& header, Commons::StreamReader& reader)
        {
            switch (header.getMagic())
            {
            case ChunkHeader::CHUNK_MODEL_HEAD:
                ModelHeadChunk::read(reader, mCurModel);
                break;
            case ChunkHeader::CHUNK_MODEL_VERTICES:
                checkCurModel();
                ModelVerticesChunk::read(reader, mCurModel);
                break;
            case ChunkHeader::CHUNK_MODEL_UVS:
                checkCurModel();
                ModelUVsChunk::read(reader, mCurModel);
                break;
            case ChunkHeader::CHUNK_MODEL_FACES:
                checkCurModel();
                ModelFacesChunk::read(reader, mCurModel);
                break;
            case ChunkHeader::CHUNK_MODEL_MATERIALS:
                checkCurModel();
                ModelMaterialsChunk::read(reader, mCurModel);
                break;
            case ChunkHeader::CHUNK_MODEL_FACE_MATERIALS:
                checkCurModel();
                ModelFaceMaterialsChunk::read(reader, mCurModel);
                break;
            case ChunkHeader::CHUNK_NULL:
                checkCurModel();
                mReadCallback(mCurModel);
                mCurModel.reset();
                break;
            default:
                return false;
            }
            return true;
        }

        void ModelSerializer::read(const Commons::IOStreamPtr& stream, TReadCallback callback)
        {
            assert(stream);
            assert(callback);

            mReadCallback = callback;
            doRead(stream);
        }

        void ModelSerializer::write(const Commons::IOStreamPtr& stream, TWriteCallback callback)
        {
            assert(stream);
            assert(callback);

            FileHeader header;
            ChunkWriter writer(stream, header);
            while (const ModelPtr model = callback())
            {
                ModelHeadChunk::write(writer, model);
                ModelVerticesChunk::write(writer, model);
                ModelUVsChunk::write(writer, model);
                ModelFacesChunk::write(writer, model);
                ModelMaterialsChunk::write(writer, model);
                ModelFaceMaterialsChunk::write(writer, model);
                writer.writeNullChunk();
            }
            writer.finish();
        }
    }
}
