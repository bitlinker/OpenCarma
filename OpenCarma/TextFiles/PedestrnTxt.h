#pragma once
#include <TextReader.h>
#include <vector>
#include <stdint.h>
#include <map>

namespace OpenCarma
{
	class PedInfo
	{
	public:
		uint32_t m_id;
		float m_height;
		uint32_t m_points;
		uint32_t m_hitPoints;
		std::vector<uint32_t> m_explodeNoises;
		uint32_t m_fallindNoise;
		float m_acceleration;
		uint32_t m_imageId;
		std::string m_shadetab;
		std::string m_pixelmap;
		std::string m_material;
		uint32_t m_actionIdFatalCarImpact;
		uint32_t m_actionIdNonFatalCarImpact;
		uint32_t m_actionIdAfterNonFatalImpact;
		uint32_t m_actionIdFatalFalling;
		uint32_t m_actionIdNonFatalFalling;
		uint32_t m_actionIdGiblets;

		// TODO: actions
		// TODO: sequences
	};

	class PedestrnTxt
	{
	public:
		PedestrnTxt(const TextReader& reader);
	};
}
