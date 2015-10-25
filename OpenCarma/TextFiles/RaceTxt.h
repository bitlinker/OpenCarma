#pragma once
#include <TextReader.h>
#include <vector>
#include <stdint.h>
#include <map>
#include <glm/glm.hpp>

namespace OpenCarma
{
	class RaceTxt
	{
	public:
		static const uint32_t SKILL_LEVELS = 3;

		// TODO: memset all
		class CheckpointQuad
		{
		public:
			glm::vec3 points[4];

		public:
			void CheckpointQuad::parse(const TextReader& reader);
		};

		class Checkpoint
		{
		public:
			uint32_t m_timerInc[SKILL_LEVELS];
			uint32_t m_timerIncNoPeds[SKILL_LEVELS];
			std::vector<CheckpointQuad> m_quads;
			uint32_t m_u1[2];
			uint32_t m_u2[2];

		public:
			void parse(const TextReader& reader);
		};

		class SpecialEffectVolume
		{
		public:
			bool m_isWater; // DEFAULT WATER or NEW IMPROVED!
			// if NEW IMPROVED, then bounding box follows
			glm::vec3 m_points[4];
			float m_gravityMultiplier;
			float m_ViscosityMultiplier;
			float m_carDamagePerMs;
			float m_pedDamagePerMs;
			uint32_t m_camEffectIndex;
			uint32_t m_skyColor;
			std::string m_windscreenMaterial;
			uint32_t m_entrySound;
			uint32_t m_exitSound;
			uint32_t m_engineNoiseSound;
			uint32_t m_materialIndex;

		public:
			void parse(const TextReader& reader);
		};

		class PedInstruction // TODO: make polymorfic if more instructions found
		{
		public:
			enum Type
			{
				INSTR_POINT,
				INSTR_REVERSE,
			};

			Type m_type;
			glm::vec3 m_point;
		public:
			void parse(const TextReader& reader);
		};

		class Pedestrian
		{
		public:
			uint32_t m_refNum;
			uint32_t m_initInstr;
			std::vector<PedInstruction> m_instructions;

		public:
			void parse(const TextReader& reader);
		};

		class OpPathSection
		{
		public:
			uint32_t m_firstNode;
			uint32_t m_secondNode;
			uint32_t m_u1[2]; // 0, 255
			uint32_t m_u2[2]; // 0, 255
			float m_accel; //? 0-1
			uint32_t m_someFlag; // 0,1

		public:
			void parse(const TextReader& reader);
		};

		class MaterialModifier
		{
		public:
			float m_carWallFriction;
			float m_tireRoadFriction;
			float m_downForce;
			float m_bumpiness;
			int32_t m_tireSoundId;
			int32_t m_crashSoundId;
			int32_t m_scrapeSoundId;
			float m_sparkiness;
			uint32_t m_expansion;
			std::string m_skidmarkMaterial;

		public:
			void parse(const TextReader& reader);
		};

		class SmokeShadetab
		{
		public:
			uint32_t m_colors[3]; // RGB TODO: convert
			float m_strengths[3];

		public:
			void parse(const TextReader& reader);
		};

		class StartPoint
		{
		public:
			glm::vec3 m_pos;
			float m_rotation;

		public:
			void parse(const TextReader& reader);
		};

		class CopStartPoint
		{
		public:
			glm::vec3 m_pos;
			glm::vec3 m_rot;

		public:
			void parse(const TextReader& reader);
		};

	public:
		RaceTxt(const TextReader& reader);

	private:
		void readVersion(const TextReader& reader);
		void readCommonData(const TextReader& reader);
		void readCheckpoints(const TextReader& reader);
		void readRenderFiles(const TextReader& reader);
		void readHorizonStuff(const TextReader& reader);
		void readSpecialEffectVolumes(const TextReader& reader);
		void readWindScreenInfo(const TextReader& reader);
		void readMinimapInfo(const TextReader& reader);
		void readFunc(const TextReader& reader);
		void readGroove(const TextReader& reader);
		void readPeds(const TextReader& reader);
		void readOpPaths(const TextReader& reader);
		void readMaterialModifiers(const TextReader& reader);
		void readNonCarObjects(const TextReader& reader);
		void readSmokeShadetables(const TextReader& reader);
		void readNetStartPoints(const TextReader& reader);
		void readSplashScreenFiles(const TextReader& reader);
		void readFooter(const TextReader& reader);

	public:
		// Fields in same order as they are in file:

		// Version 6 is latest and has all features
		// Version 5 has no lo-mem materials and models
		// ...
		uint32_t m_version;

		StartPoint m_grid;		
		uint32_t m_initialTimer[SKILL_LEVELS];
		uint32_t m_numLaps;
		uint32_t m_completedBonusAllLaps[SKILL_LEVELS];
		uint32_t m_completedBonusAllPeds[SKILL_LEVELS];
		uint32_t m_completedBonusAllOppos[SKILL_LEVELS];
		uint32_t m_checkPointSize1[2]; // w, h, ???
		uint32_t m_checkPointSize2[2];

		std::vector<Checkpoint> m_checkpoints;

		// Render files
		std::vector<std::string> m_pixelMapFiles;
		std::vector<std::string> m_pixelMapFilesLowRes;
		std::vector<std::string> m_shadeTabFiles;
		std::vector<std::string> m_materialFiles;
		std::vector<std::string> m_materialFilesLowRes;
		std::vector<std::string> m_modelFiles;
		std::vector<std::string> m_modelFilesLowRes;
		std::string m_trackActor;
		std::string m_trackActorLowRes;
		std::string m_trackActorAdditional;

		// Horizon stuff
		enum SkyCueMode
		{
			CUE_NONE,
			CUE_DARK,
			CUE_FOG
		};
		std::string m_skyTexture; // Or "none"
		uint32_t m_skyHorizRepeats;
		uint32_t m_skyVertSize; // In degrees
		uint32_t m_skyPosition; // Points below top
		SkyCueMode m_skyCueMode;
		uint32_t m_skyDegree[2]; // Fog / darkness
		
		// Default engine noise 
		uint32_t m_defaultEngineNoise;

		// Special effect volumes
		std::vector<SpecialEffectVolume> m_specialEffectVolumes;

		// Wind screen materials
		std::string m_wndScrnMatDefault;
		std::string m_wndScrnMatDarkness;
		std::string m_wndScrnMatFog;

		// Minimap
		std::string m_mapPixelmap;
		glm::mat3x4 m_mapMatrix; // World->map

		// Func
		// TODO

		// Groove
		// TODO

		// Pedestrian stuff
		uint32_t m_pedSubTableIndex;
		std::vector<Pedestrian> m_peds;

		// Opponent paths
		std::vector<glm::vec3> m_opPathNodes;
		std::vector<OpPathSection> m_opPathSections;
		std::vector<CopStartPoint> m_copStartPoints;

		// Material modifiers
		std::vector<MaterialModifier> m_materialModifiers;

		// Non-car object files
		std::vector<std::string> m_nonCarObjectFiles;

		// Smoke shadetabs
		std::vector<SmokeShadetab> m_smokeShadetabs;

		// Network start points
		std::vector<StartPoint> m_netStartPoints;

		// Splash screen files
		std::vector<std::string> m_splashScreenFiles;

		// Footer
		float m_yonMultiplier;
		std::string m_selfName;
	};
}
