#include "RenderMaterial.h"

namespace OpenCarma
{
	namespace Render
	{
		RenderMaterial::RenderMaterial(const BRender::MaterialPtr& material, Commons::Render::Render& render)
		{
			// TODO: init from material
		}

		RenderMaterial::~RenderMaterial()
		{
		}

		void RenderMaterial::set()
		{
			if (m_shader)
			{
				m_shader->use();

				// TODO: set states
				//m_shader->setUniformMatrix()
			}

			for (auto tex : m_textures)
			{
				tex->bind();
			}
		}
	}
}