#pragma once
#include "Common.h"
#include "Object.h"

namespace OpenCarma
{
	namespace BRender
	{
        class BR_API Pixmap : public Object
		{
		public:
			Pixmap();

			// TODO: getters

		private:
			uint32_t m_width, m_height, m_stride;
			std::vector<uint8_t> m_pixels;
			std::string m_name;
		};
	}
}
