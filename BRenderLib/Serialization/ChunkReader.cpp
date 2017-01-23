#include <Serialization/ChunkReader.h>
#include <Exception/Exception.h>
#include <Common/StringUtils.h>
#include <cassert>

using namespace Commons;

namespace OpenCarma
{
	namespace BRender
	{
		void ChunkReader::deserialize(const IOStreamPtr& stream, ChunkReaderListener* listener)
		{
			assert(stream);
			assert(listener);

			StreamReader reader(stream, Endianness::BIG_ENDIAN);

			FileHeaderChunk fileHeader;
			fileHeader.read(reader);
			// TODO: check size & versions
			//fileHeader.getSize();

			listener->onStart();

			ChunkHeader header;
			IOStream::size_type streamSize = reader.size();
			while (reader.tell() < streamSize)
			{
				header.read(reader);
				uint32_t lastOffset = reader.tell();

				if (!listener->onChunkRead(header, reader))
				{
					throw SerializationException(StringUtils::FormatString("Unknown chunk: %d at %d", header.getMagic(), reader.tell()));
				}

				IOStream::size_type redSize = reader.tell() - lastOffset;
				if (redSize != header.getSize())
				{
					throw SerializationException(StringUtils::FormatString("Incorrect chunk size read: required: %d, current %d", header.getSize(), redSize));
				}
			}
			listener->onFinish();
		};
	}
}