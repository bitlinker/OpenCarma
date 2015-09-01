#include "Camera.h"

namespace OpenCarma
{
	Camera::Camera()
		: m_proj()
		, m_pos()
		, m_rot()
		, m_isModelViewDirty(true)
	{
	}


	Camera::~Camera()
	{
	}

	void Camera::setPerspective(float fovy, float aspect, float far, float near)
	{
		m_proj = glm::perspective(fovy, aspect, near, far);
	}

	void Camera::setOrtho(float left, float top, float right, float bottom, float far, float near)
	{
		m_proj = glm::ortho(left, right, bottom, top, near, far);
	}

	const glm::vec3 Camera::getTranslation() const
	{
		return m_pos;
	}

	void Camera::setTranslation(const glm::vec3& pos)
	{
		m_pos = pos; 
		m_isModelViewDirty = true;
	}

	const glm::quat Camera::getRotation() const
	{
		return m_rot;
	}

	void Camera::setRotation(const glm::quat& rotation)
	{
		m_rot = rotation;
		m_isModelViewDirty = true;
	}

	const glm::mat4 Camera::getModelview() const
	{
		if (m_isModelViewDirty)
		{
			m_modelView = glm::mat4();
			m_modelView *= glm::translate(-m_pos);
			m_modelView *= glm::mat4_cast(-m_rot);
			m_isModelViewDirty = false;			
		}
		return m_modelView;
	}
}