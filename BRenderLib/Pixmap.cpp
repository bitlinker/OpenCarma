#include "Pixmap.h"
#include "Chunk.h"

namespace OpenCarma
{
	namespace BRender
	{
		Pixmap::Pixmap() :
			m_width(0),
			m_height(0),
			m_stride(0)
		{
		}

		bool fromStream()
		{
			Chunk chunk;

			// TODO
			return true;
		}
	}
}
