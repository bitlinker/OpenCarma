#pragma once
#include "Common.h"

namespace OpenCarma
{
	namespace BRender
	{
		// BRender palette
		class BR_API Palette
		{
		public:
			Palette();
			~Palette();

			bool fromStream();

		private:
			std::vector<uint32_t> colors;
		};

	}
}