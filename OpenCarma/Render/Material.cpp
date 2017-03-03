#include <Material.h>

using namespace Commons::Render;

namespace OpenCarma
{
	namespace Render
	{
		Material::Material(const OpenCarma::BRender::MaterialPtr& mat)
		{
		}

		Material::~Material()
		{
		}

        void Material::use(Context* context)
        {
            // TODO
        }

		//void Material::set()
		//{
		//	if (m_shader)
		//	{
		//		m_shader->use();

		//		// TODO: set states
		//		//m_shader->setUniformMatrix()
		//	}

		//	for (auto tex : m_textures)
		//	{
		//		tex->bind();
		//	}
		//}
	}
}