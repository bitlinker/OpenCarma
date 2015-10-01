#pragma once
#include <Render/Camera.h>

namespace OpenCarma
{
	class FreeFlyCameraController
	{
	public:
		explicit FreeFlyCameraController(const Commons::Render::CameraPtr& camera);

		void update(float delta);

	private:
		Commons::Render::CameraPtr m_camera; // TODO: weak?

		glm::vec3 m_angles;
	};
}
