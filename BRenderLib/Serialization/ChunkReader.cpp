#include <Serialization/ChunkReader.h>
#include <Streams/StreamReader.h>
#include <Serialization/ChunkHeader.h>
#include <Exception/Exception.h>
#include <Common/StringUtils.h>
#include <Logger/Log.h>
#include <cassert>

using namespace Commons;

namespace OpenCarma
{
	namespace BRender
	{
		void ChunkReader::doRead(const IOStreamPtr& stream)
		{
			assert(stream);
            LOG_DEBUG("Begin reading stream %d", stream);

			StreamReader reader(stream, Endianness::BIG_ENDIAN);

            ChunkHeader header;
			IOStream::size_type streamSize = reader.size();
            bool hasFileHeader = false;
			while (reader.tell() < streamSize)
			{
				header.read(reader);
                LOG_DEBUG("Chunk type %d, size %d at %d", header.getMagic(), header.getSize(), reader.tell());
				uint32_t lastOffset = reader.tell();

                if (header.getMagic() == ChunkHeader::CHUNK_FILE_HEADER)
                {
                    FileHeader fileHeader;
                    fileHeader.read(reader);
                    onStart(fileHeader);
                    hasFileHeader = true;
                }
                else // Generic chunk
                {
                    if (!hasFileHeader) throw SerializationException("File header is missing");
                    if (header.getMagic() == 0 && !(header == ChunkHeader::NULL_CHUNK)) throw SerializationException("Invalid null chunk");

                    if (!onChunkRead(header, reader))
                    {
                        throw SerializationException(StringUtils::FormatString("Unknown chunk: %d at %d", header.getMagic(), reader.tell()));
                    }
                }

				IOStream::size_type redSize = reader.tell() - lastOffset;
				if (redSize != header.getSize()	&&
					(header.getMagic() != ChunkHeader::CHUNK_ACTOR_MODEL_NAME
					&& header.getMagic() != ChunkHeader::CHUNK_ACTOR_MATERIAL_NAMES
					&& header.getMagic() != ChunkHeader::CHUNK_ACTOR_MATERIAL_NAMES)
				) // BUGFIX: Model name or material name in actor has incorrect size
				{
					throw SerializationException(StringUtils::FormatString("Incorrect chunk size read: required: %d, current %d", header.getSize(), redSize));
				}
			}
			onFinish();
		};
	}
}