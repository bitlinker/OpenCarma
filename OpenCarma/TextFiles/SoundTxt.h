#pragma once
#include <TextReader.h>
#include <vector>
#include <stdint.h>
#include <map>

namespace OpenCarma
{
	class SoundEntry
	{
	public:
		SoundEntry(const TextReader& reader);

	public:
		// Comments are from original carma file
		uint32_t m_id;									// Sound ID
		uint32_t m_typeId;								// Type
		uint32_t m_flags;								// Flags
		std::string m_filename;							// File name
		uint32_t m_priority;							// Priority
		uint32_t m_repeatRate;							// Repeat rate
		uint32_t m_minVol, m_maxVol;					// MinVol, MaxVol
		float m_minPitch, m_maxPitch;					// MinPitch, MaxPitch
		float m_minSpeed, m_maxSpeed;					// MinSpeed, MaxSpeed
		uint32_t m_specialFxId;							// Special FX index
		std::vector<uint32_t> m_lowMemAlternatives;
	};

	class SoundTxt
	{
	private:
		typedef std::map<uint32_t, SoundEntry> TEntryMap;
		TEntryMap m_entries;

	public:
		SoundTxt(const TextReader& reader);
		const TEntryMap& getEntries() const { return m_entries; };
	};
}
