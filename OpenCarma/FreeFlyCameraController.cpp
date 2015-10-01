#include "FreeFlyCameraController.h"

// TODO: input system
#include <windows.h>

namespace OpenCarma
{
	static bool CheckKey(int key)
	{
		return ::GetAsyncKeyState(key) & 0x8000;
	}

	static glm::vec2 GetMousePos()
	{
		POINT p;
		::GetCursorPos(&p);
		return glm::vec2(p.x, p.y);
	}

	FreeFlyCameraController::FreeFlyCameraController(const Commons::Render::CameraPtr& camera)
		: m_camera(camera)
	{
	}

	void FreeFlyCameraController::update(float delta)
	{
		// Translation:
		glm::vec3 direction;

		if (CheckKey('W'))
		{
			direction += glm::vec3(0.F, 0.F, -1.F);
		}		
		else if (CheckKey('S'))
		{
			direction += glm::vec3(0.F, 0.F, 1.F);
		}

		if (CheckKey('A'))
		{
			direction += glm::vec3(-1.F, 0.F, 0.F);
		}
		else if (CheckKey('D'))
		{
			direction += glm::vec3(1.F, 0.F, 0.F);
		}

		if (CheckKey('Q'))
		{
			direction += glm::vec3(0.F, 1.F, 0.F);
		}
		else if (CheckKey('E'))
		{
			direction += glm::vec3(0.F, -1.F, 0.F);
		}

		glm::vec3 translation = m_camera->getTranslation() + direction * delta;
		m_camera->setTranslation(translation);

		// Rotation:
		// TODO: get current or store rotation and translation in controller?

		//if (CheckKey('M')) // Mouse update
		{
			glm::vec3 angleSpeed;

			if (CheckKey(VK_LEFT))
			{
				angleSpeed += glm::vec3(-1.F, 0.F, 0.F);
			}
			else if (CheckKey(VK_RIGHT))
			{
				angleSpeed += glm::vec3(1.F, 0.F, 0.F);
			}

			if (CheckKey(VK_UP))
			{
				angleSpeed += glm::vec3(0.F, 1.F, 0.F);
			}
			else if (CheckKey(VK_DOWN))
			{
				angleSpeed += glm::vec3(0.F, -1.F, 0.F);
			}
		
			m_angles.x += (angleSpeed.y * delta); // Yaw
			m_angles.y += (angleSpeed.x * delta); // Pitch
			m_angles.z = 0.F; // Roll
		}
		
		glm::quat rotation = glm::quat(m_angles);
		m_camera->setRotation(rotation);
	}
}