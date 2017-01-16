#include <cassert>
#include <sstream>
#include <Serialization/MaterialSerializer.h>
#include <EndianStreamReader.h>
#include <Exception/Exception.h>

namespace OpenCarma
{
    namespace BRender
    {
        void MaterialSerializer::DeserializeMaterial(std::istream& stream, std::vector<MaterialPtr>& materials)
        {
            if (!stream)
                throw Commons::IOException("Stream is not opened");

            MaterialPtr curMat;

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
                else if (header.getMagic() == MaterialAttributesV1Chunk::MAGIC)
                {
                    curMat = MaterialPtr(new Material());
                    assert(curMat.get());
                    curMat->m_header.read(reader);
                }
                else if (header.getMagic() == MaterialAttributesV2Chunk::MAGIC)
                {
                    // TODO
                    throw "Unimplemented";
                }
                else if (header.getMagic() == MaterialPixmapNameChunk::MAGIC)
                {
                    curMat->m_pixelmap.read(reader);
                }
                else if (header.getMagic() == MaterialShadetabNameChunk::MAGIC)
                {
                    curMat->m_shadetab.read(reader);
                }
                else if (header.isNULL())
                {
                    if (!curMat.get() || !curMat->isValid())
                        throw Commons::SerializationException("Material object is incorrect");
                    materials.push_back(curMat);
                    curMat.reset();
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
                    //throw SerializationException(ss.str()); TODO: warning?
                }
            }
        }

        void MaterialSerializer::SerializeMaterial(const MaterialPtr& pal, std::ostream& stream)
        {
            assert(pal);

            if (!stream)
                throw Commons::IOException("Stream is not opened");

            // TODO
        }
    }
}