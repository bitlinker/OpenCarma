#pragma once
#include <memory>
#include <RenderCommon.h>

namespace OpenCarma
{
	class Camera
	{
	public:
		Camera();
		~Camera();

		void setPerspective(float fovy, float aspect, float far, float near);
		void setOrtho(float left, float top, float right, float bottom, float far, float near);

		const glm::mat4 getProjection() const { return m_proj; };
		const glm::mat4 getModelview() const;

		const glm::vec3 getTranslation() const;
		void setTranslation(const glm::vec3& pos);

		const glm::quat getRotation() const;
		void setRotation(const glm::quat& rotation);

	private:
		glm::mat4 m_proj;

		glm::vec3 m_pos;
		glm::quat m_rot;

		// Matrix cache
		mutable glm::mat4 m_modelView;
		mutable bool m_isModelViewDirty;
	};

	typedef std::shared_ptr<Camera> CameraPtr;
}