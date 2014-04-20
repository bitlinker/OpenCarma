#pragma once
#include "Common.h"

namespace OpenCarma
{
	namespace BRender
	{
		// TODO
		class BR_API Chunk
		{
		private:
			uint32_t m_magic;
			uint32_t m_size;
		};

		class BR_API Pixmap
		{
		public:
			Pixmap(void);
			~Pixmap(void);
		private:
			uint32_t width, height, stride;
			std::vector<uint8_t> m_pixels;
		};
	}
}
