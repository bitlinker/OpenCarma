#pragma once
#include "Common.h"

namespace OpenCarma
{
	namespace BRender
	{
		// todo
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
		};
	}
}
