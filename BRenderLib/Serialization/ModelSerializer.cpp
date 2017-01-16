#include <cassert>
#include <sstream>
#include <Serialization/ModelSerializer.h>
#include <EndianStreamReader.h>
#include <Exception/Exception.h>

namespace OpenCarma
{
    namespace BRender
    {
        // TODO: common deserializer loop?
        void ModelSerializer::DeserializeModels(std::istream& stream, std::vector<ModelPtr>& models)
        {
            if (!stream)
                throw Commons::IOException("Stream is not opened");

            ModelPtr curModel;

            EndianStreamReader reader(stream, Commons::Endianness::BIG_ENDIAN);

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
                else if (header.getMagic() == ModelHeadChunk::MAGIC)
                {
                    curModel = ModelPtr(new Model());
                    assert(curModel.get());
                    curModel->m_header.read(reader);
                }
                else if (header.getMagic() == ModelVerticesChunk::MAGIC)
                {
                    assert(curModel.get());
                    curModel->m_vertices.read(reader);
                }
                else if (header.getMagic() == ModelUVsChunk::MAGIC)
                {
                    assert(curModel.get());
                    curModel->m_uv.read(reader);
                }
                else if (header.getMagic() == ModelFacesChunk::MAGIC)
                {
                    assert(curModel.get());
                    curModel->m_faces.read(reader);
                }
                else if (header.getMagic() == ModelMaterialsChunk::MAGIC)
                {
                    assert(curModel.get());
                    curModel->m_materials.read(reader);
                }
                else if (header.getMagic() == ModelFaceMaterialsChunk::MAGIC)
                {
                    assert(curModel.get());
                    curModel->m_faceMats.read(reader);
                }                                
                else if (header.isNULL())
                {
                    if (!curModel.get() || !curModel->isValid())
                        throw Commons::SerializationException("Model object is incorrect");
                    models.push_back(curModel);
                    curModel.reset();
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
                    //throw SerializationException(ss.str());
                    // TODO: warning
                }
            }
        }
    }
}