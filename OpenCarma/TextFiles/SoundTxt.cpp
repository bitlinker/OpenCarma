#include <SoundTxt.h>
#include <Log.h>
#include <Exception/Exception.h>

namespace OpenCarma
{
	SoundEntry::SoundEntry(const TextReader& reader)
	{
		reader.readUInt32(m_id);
		reader.readUInt32_2(m_typeId, m_flags);
		reader.readLine(m_filename);
		reader.readUInt32(m_priority);
		reader.readUInt32(m_repeatRate);
		reader.readUInt32_2(m_minVol, m_maxVol);
		reader.readFloat_2(m_minPitch, m_maxPitch);
		reader.readFloat_2(m_minSpeed, m_maxSpeed);
		reader.readUInt32(m_specialFxId);

		uint32_t numLowMemAlternatives = 0;
		reader.readUInt32(numLowMemAlternatives);
		m_lowMemAlternatives.resize(numLowMemAlternatives);
		for (uint32_t i = 0; i < numLowMemAlternatives; ++i)
			reader.readUInt32(m_lowMemAlternatives[i]);
	}

	SoundTxt::SoundTxt(const TextReader& reader)
		: m_entries()
	{
		while (!reader.isEOF())
		{
			try { // It's the only way to check if there are no other entries in file if there are empty string in the end. I know its ugly.
				SoundEntry entry(reader);
				LOG_DEBUG("Adding sound entry %d: filename %s", entry.m_id, entry.m_filename.data());
				m_entries.insert(std::make_pair(entry.m_id, entry));
			}
			catch (const Commons::EOFException&) {
				break;
			}
		}
	}
}