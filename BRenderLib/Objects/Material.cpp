#include <Objects/Material.h>

namespace OpenCarma
{
	namespace BRender
	{
		Material::Material()
            : m_header()
            , m_pixelmap()
            , m_shadetab()
		{
		}

        bool Material::isValid() const
        {
            // TODO: implement
            return true;
        }
	}
}