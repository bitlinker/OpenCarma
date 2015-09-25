#pragma once
#include <stdint.h>

namespace OpenCarma
{
	class SoundMgr
	{
	public:
		SoundMgr();
		~SoundMgr();

		void playSound(uint32_t id);

	private:
	};
}
