#include <algorithm>
#include <RaceTxt.h>
#include <Logger/Log.h>
#include <Exception/Exception.h>

namespace OpenCarma
{
	void RaceTxt::Checkpoint::parse(const TextReader& reader)
	{
		reader.readUInt32Vec(m_timerInc, SKILL_LEVELS);
		reader.readUInt32Vec(m_timerIncNoPeds, SKILL_LEVELS);

		uint32_t numQuads = 0;
		reader.readUInt32(numQuads);
		m_quads.resize(numQuads);
		for (uint32_t i = 0; i < numQuads; ++i)
		{
			m_quads[i].parse(reader);
		}
		reader.readUInt32Vec(&m_u1[0], 2);
		reader.readUInt32Vec(&m_u2[0], 2);
	}

	void RaceTxt::CheckpointQuad::parse(const TextReader& reader)
	{
		for (uint32_t k = 0; k < 4; ++k)
		{
			reader.readFloatVec(&points[k].x, 3);
		}
	}

	void RaceTxt::SpecialEffectVolume::parse(const TextReader& reader)
	{
		std::string strTmp;
		reader.readLine(strTmp);
		if (strTmp == "DEFAULT WATER")
		{
			m_isWater = true;
		}
		else if (strTmp == "NEW IMPROVED!")
		{
			m_isWater = false;
			for (uint32_t i = 0; i < 4; ++i)
			{
				reader.readFloatVec(&m_points[i].x, 3);
			}			
		}
		else
			throw Commons::SerializationException("Unknown special effect volume type");
		
		reader.readFloat(m_gravityMultiplier);
		reader.readFloat(m_ViscosityMultiplier);
		reader.readFloat(m_carDamagePerMs);
		reader.readFloat(m_pedDamagePerMs);
		reader.readUInt32(m_camEffectIndex); // TODO: signed?
		reader.readUInt32(m_skyColor);
		reader.readLine(m_windscreenMaterial);
		reader.readUInt32(m_entrySound);
		reader.readUInt32(m_exitSound);
		reader.readUInt32(m_engineNoiseSound);
		reader.readUInt32(m_materialIndex);		
	}

	void RaceTxt::Pedestrian::parse(const TextReader& reader)
	{
		reader.readUInt32(m_refNum);
		uint32_t numInstr = 0;
		reader.readUInt32(numInstr);
		reader.readUInt32(m_initInstr);
		m_instructions.resize(numInstr);
		std::for_each(m_instructions.begin(), m_instructions.end(), [reader](PedInstruction& i){ i.parse(reader); });
	}

	static RaceTxt::PedInstruction::Type ParsePedInstrType(const std::string& str)
	{
		if (str == "point")
			return RaceTxt::PedInstruction::INSTR_POINT;
		else if (str == "reverse")
			return RaceTxt::PedInstruction::INSTR_REVERSE;
		else
			throw Commons::SerializationException("Unknown ped instruction type");
	}

	void RaceTxt::PedInstruction::parse(const TextReader& reader)
	{
		std::string tmpStr;
		reader.readLine(tmpStr);
		m_type = ParsePedInstrType(tmpStr);
		if (m_type == INSTR_POINT)
		{
			reader.readFloatVec(&m_point.x, 3);
		}
	}

	void RaceTxt::OpPathSection::parse(const TextReader& reader)
	{
		std::string line;
		reader.readLine(line);

		sscanf(line.c_str(),
			"%d, %d, %d, %d, %d, %d, %f, %d",
			&m_firstNode,
			&m_secondNode,
			&m_u1[0],
			&m_u1[1],
			&m_u2[0],
			&m_u2[1],
			&m_accel,
			&m_someFlag
			);	
	}

	void RaceTxt::MaterialModifier::parse(const TextReader& reader)
	{
		reader.readFloat(m_carWallFriction);
		reader.readFloat(m_tireRoadFriction);
		reader.readFloat(m_downForce);
		reader.readFloat(m_bumpiness);
		reader.readSInt32(m_tireSoundId);
		reader.readSInt32(m_crashSoundId);
		reader.readSInt32(m_scrapeSoundId);
		reader.readFloat(m_sparkiness);
		reader.readUInt32(m_expansion);
		reader.readLine(m_skidmarkMaterial);
	}

	void RaceTxt::SmokeShadetab::parse(const TextReader& reader)
	{
		reader.readUInt32Vec(m_colors, 3);
		reader.readFloatVec(m_strengths, 3);
	}

	void RaceTxt::StartPoint::parse(const TextReader& reader)
	{
		reader.readFloatVec(&m_pos.x, 3);
		reader.readFloat(m_rotation);
	}

	void RaceTxt::CopStartPoint::parse(const TextReader& reader)
	{
		// TODO: tricky. Should be aligned properly to work
		reader.readFloatVec(&m_pos.x, 6);
	}	

	// TODO implement me!
	RaceTxt::RaceTxt(const TextReader& reader)
	{
		readVersion(reader);
		readCommonData(reader);
		readCheckpoints(reader);
		readRenderFiles(reader);
		readHorizonStuff(reader);
		readSpecialEffectVolumes(reader);
		readWindScreenInfo(reader);
		readMinimapInfo(reader);
		readFunc(reader);
		readGroove(reader);
		readPeds(reader);
		readOpPaths(reader);
		readMaterialModifiers(reader);
		readNonCarObjects(reader);
		readSmokeShadetables(reader);
		readNetStartPoints(reader);
		readSplashScreenFiles(reader);
		readFooter(reader);
	}

	void RaceTxt::readVersion(const TextReader& reader)
	{
		std::string line;
		reader.readLine(line);		
		if (line.compare(0, 7, "VERSION") != 0)
			throw Commons::SerializationException("Wrong race TXT file: version not found: " + line);

		m_version = static_cast<uint32_t>(stoi(line.substr(8)));
		if (m_version != 5 && m_version != 6)
			throw Commons::SerializationException("Wrong race TXT file: unsupported version: " + line);
	}

	void RaceTxt::readCommonData(const TextReader& reader)
	{
		m_grid.parse(reader);
		reader.readUInt32Vec(m_initialTimer, SKILL_LEVELS);
		reader.readUInt32(m_numLaps);
		reader.readUInt32Vec(m_completedBonusAllLaps, SKILL_LEVELS);
		reader.readUInt32Vec(m_completedBonusAllPeds, SKILL_LEVELS);
		reader.readUInt32Vec(m_completedBonusAllOppos, SKILL_LEVELS);
		reader.readUInt32Vec(m_checkPointSize1, 2);
		reader.readUInt32Vec(m_checkPointSize2, 2);
	}

	void RaceTxt::readCheckpoints(const TextReader& reader)
	{
		uint32_t numCheckpoints = 0;
		reader.readUInt32(numCheckpoints);
		m_checkpoints.resize(numCheckpoints);
		for (uint32_t i = 0; i < numCheckpoints; ++i)
		{
			m_checkpoints[i].parse(reader);
		}
	}

	// Helper method to read number followed by list of string: i.e. list of pixelmaps
	static void ReadStringList(const TextReader& reader, std::vector<std::string>& strings)
	{
		uint32_t numFiles = 0;
		reader.readUInt32(numFiles);
		strings.resize(numFiles);
		for (uint32_t i = 0; i < numFiles; ++i)
		{
			reader.readLine(strings[i]);
		}
	}

	void RaceTxt::readRenderFiles(const TextReader& reader)
	{
		// TODO: check version here...
		ReadStringList(reader, m_pixelMapFiles);
		ReadStringList(reader, m_pixelMapFilesLowRes);
		ReadStringList(reader, m_shadeTabFiles);
		ReadStringList(reader, m_materialFiles);
		ReadStringList(reader, m_materialFilesLowRes);
		ReadStringList(reader, m_modelFiles);
		if (m_version >= 6) {
			ReadStringList(reader, m_modelFilesLowRes);
		}
		reader.readLine(m_trackActor);
		if (m_version >= 6) {
			reader.readLine(m_trackActorLowRes);
		}
		reader.readLine(m_trackActorAdditional);
	}

	static RaceTxt::SkyCueMode ParseSkyCueStr(std::string& str)
	{
		if (str == "none")
			return RaceTxt::CUE_NONE;
		else if (str == "dark")
			return RaceTxt::CUE_DARK;
		else if (str == "fog")
			return RaceTxt::CUE_FOG;
		else
		{
			LOG_WARN("Unknown sky cue mode: %s", str.data());
			return RaceTxt::CUE_NONE;
		}		
	}

	void RaceTxt::readHorizonStuff(const TextReader& reader)
	{
		reader.readLine(m_skyTexture);
		reader.readUInt32(m_skyHorizRepeats);
		reader.readUInt32(m_skyVertSize);
		reader.readUInt32(m_skyPosition);
		std::string cueModeStr;
		reader.readLine(cueModeStr);
		m_skyCueMode = ParseSkyCueStr(cueModeStr);
		reader.readUInt32Vec(m_skyDegree, 2);
		reader.readUInt32(m_defaultEngineNoise);
	}

	void RaceTxt::readSpecialEffectVolumes(const TextReader& reader)
	{
		uint32_t numVolumes = 0;
		reader.readUInt32(numVolumes);
		m_specialEffectVolumes.resize(numVolumes);
		for (uint32_t i = 0; i < numVolumes; ++i)
		{
			m_specialEffectVolumes[i].parse(reader); // TODO: replace with iterators?
		}
	}

	void RaceTxt::readWindScreenInfo(const TextReader& reader)
	{
		reader.readLine(m_wndScrnMatDefault);
		reader.readLine(m_wndScrnMatDarkness);
		reader.readLine(m_wndScrnMatFog);
		reader.skipLines(1);
	}

	void RaceTxt::readMinimapInfo(const TextReader& reader)
	{
		reader.readLine(m_mapPixelmap);

		// Matrix is somehow broken here...
		// The second row has no ',' between numbers
		// So use custom matrix reader implementation
		float data[12] = {0};
		reader.readFloatVec(&data[0], 3);
		reader.skipLines(1);
		reader.readFloatVec(&data[6], 3);
		reader.readFloatVec(&data[9], 3);

		for (uint32_t y = 0; y < 4; ++y)
			for (uint32_t x = 0; x < 3; ++x)
				m_mapMatrix[x][y] = data[x + y * 3]; // TODO: check
	}

	void RaceTxt::readFunc(const TextReader& reader)
	{
		std::string strTmp;
		reader.readLine(strTmp);
		if (strTmp != "START OF FUNK")
			throw Commons::SerializationException("expected START OF FUNK not found");

		// TODO: parse it
		while (!reader.isEOF())
		{
			reader.readLine(strTmp);
			if (strTmp == "END OF FUNK")
				break;
		}
	}

	void RaceTxt::readGroove(const TextReader& reader)
	{
		std::string strTmp;
		reader.readLine(strTmp);
		if (strTmp != "START OF GROOVE")
			throw Commons::SerializationException("expected \"START OF GROOVE\" not found");

		// TODO: parse it
		while (!reader.isEOF())
		{
			reader.readLine(strTmp);
			if (strTmp == "END OF GROOVE")
				break;
		}
	}

	void RaceTxt::readPeds(const TextReader& reader)
	{
		reader.readUInt32(m_pedSubTableIndex);
		uint32_t numPeds = 0;
		reader.readUInt32(numPeds);
		m_peds.resize(numPeds);
		std::for_each(m_peds.begin(), m_peds.end(), [reader](Pedestrian& ped) { ped.parse(reader); });
	}

	void RaceTxt::readOpPaths(const TextReader& reader)
	{
		std::string magicStr;
		reader.readLine(magicStr);
		if (magicStr != "START OF OPPONENT PATHS")
			throw Commons::SerializationException("expected \"START OF OPPONENT PATHS\" not found");

		uint32_t numPathNodes = 0;
		reader.readUInt32(numPathNodes);
		m_opPathNodes.resize(numPathNodes);
		std::for_each(m_opPathNodes.begin(), m_opPathNodes.end(),
			[reader](glm::vec3& node) {reader.readFloatVec(&node.x, 3); }
		);

		uint32_t numPathSections = 0;
		reader.readUInt32(numPathSections);
		m_opPathSections.resize(numPathSections);
		std::for_each(m_opPathSections.begin(), m_opPathSections.end(), 
			[reader](OpPathSection& section) { section.parse(reader); }
		);

		uint32_t numCopPoints = 0;
		reader.readUInt32(numCopPoints);
		m_copStartPoints.resize(numCopPoints);
		std::for_each(m_copStartPoints.begin(), m_copStartPoints.end(),
			[reader](CopStartPoint& point) { point.parse(reader); }
		);

		reader.readLine(magicStr);
		if (magicStr != "END OF OPPONENT PATHS")
			throw Commons::SerializationException("expected \"END OF OPPONENT PATHS\" not found");
	}

	void RaceTxt::readMaterialModifiers(const TextReader& reader)
	{
		uint32_t numModifiers = 0;
		reader.readUInt32(numModifiers);
		m_materialModifiers.resize(numModifiers);
		std::for_each(m_materialModifiers.begin(), m_materialModifiers.end(),
			[reader](MaterialModifier& mod) { mod.parse(reader); }
		);
	}

	void RaceTxt::readNonCarObjects(const TextReader& reader)
	{
		ReadStringList(reader, m_nonCarObjectFiles);
	}

	void RaceTxt::readSmokeShadetables(const TextReader& reader)
	{
		uint32_t numShadetabs = 0;
		reader.readUInt32(numShadetabs);
		m_smokeShadetabs.resize(numShadetabs);
		std::for_each(m_smokeShadetabs.begin(), m_smokeShadetabs.end(),
			[reader](SmokeShadetab& shadetab) { shadetab.parse(reader); }
		);
	}

	void RaceTxt::readNetStartPoints(const TextReader& reader)
	{
		uint32_t numStartPoints = 0;
		reader.readUInt32(numStartPoints);
		m_netStartPoints.resize(numStartPoints);
		std::for_each(m_netStartPoints.begin(), m_netStartPoints.end(),
			[reader](StartPoint& point) { point.parse(reader); }
		);
	}

	void RaceTxt::readSplashScreenFiles(const TextReader& reader)
	{
		ReadStringList(reader, m_splashScreenFiles);
	}

	void RaceTxt::readFooter(const TextReader& reader)
	{
		reader.readFloat(m_yonMultiplier);
		reader.readLine(m_selfName);
	}
}