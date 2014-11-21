#include "Actor.h"

namespace OpenCarma
{
	namespace BRender
	{
		Actor::Actor()
            : m_header()
            , m_matrix()
            , m_materials()
            , m_models()
            , m_bbox()
		{
		}


		Actor::~Actor()
		{
		}

        bool Actor::isValid() const
        {
            // TODO: implement
            return true;
        }
	}
}