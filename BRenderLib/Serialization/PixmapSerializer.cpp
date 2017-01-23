#include <cassert>
#include <Common/StringUtils.h>
#include <Serialization/PixmapSerializer.h>
#include <Serialization/ChunkReader.h>
#include <Streams/StreamReader.h>
#include <Exception/Exception.h>

using namespace Commons;

namespace OpenCarma
{
    namespace BRender
    {
		class BR_API FileHeaderChunk : public ChunkHeader
		{
		public:
			static const uint32_t MAGIC = 0x12;

		public:
			FileHeaderChunk();

			void read(Commons::StreamReader& reader);

		public:
			uint32_t m_version1;
			uint32_t m_version2;
		};

		FileHeaderChunk::FileHeaderChunk()
			: ChunkHeader()
			, m_version1(0)
			, m_version2(0)
		{
		}

		void FileHeaderChunk::read(Commons::StreamReader& reader)
		{
			ChunkHeader::read(reader);
			if (getMagic() != MAGIC)
			{
				throw SerializationException("Incorrect magic");
			}
			m_version1 = reader.readUInt32();
			m_version2 = reader.readUInt32();
		}

		bool PixmapSerializer::onChunk(const ChunkHeader& header, StreamReader& reader)
		{
			switch (header.getMagic())
			{
			case TextureHeadChunk::MAGIC:
				mCurPixmap = PixmapPtr(new Pixmap());
				assert(mCurPixmap.get()); // TODO: checks, not asserts
				//reader.readUInt32();
				// TODO
				//mCurPixmap->m_header.read(reader);
				break;
			case TextureDataChunk::MAGIC:
				assert(mCurPixmap.get());
				// TODO
				//mCurPixmap->mData.read(reader);
				break;
			case 0: // Null header
				assert(header.getSize() == 0);
				if (!mCurPixmap.get() || !mCurPixmap->isValid())
					throw SerializationException("Pixelmap object is incorrect");
				mPixelmaps.push_back(mCurPixmap);
				mCurPixmap.reset();
				break;
			}
		}

		const std::vector<PixmapPtr>& PixmapSerializer::deserialize(const IOStreamPtr& stream)
        {
			ChunkReader reader;
			reader.deserialize(stream, this);
			return mPixelmaps;
        }

        void PixmapSerializer::serialize(const PixmapPtr& pal, const IOStreamPtr& stream)
        {
            assert(pal);
			// TODO
			throw Exception("not implemented");
        }
    }
}