#pragma once
#include <Camera.h>

namespace OpenCarma
{
	class FreeFlyCameraController
	{
	public:
		explicit FreeFlyCameraController(const CameraPtr& camera);

		void update(float delta);

	private:
		CameraPtr m_camera; // TODO: weak?

		glm::vec3 m_angles;
	};
}
