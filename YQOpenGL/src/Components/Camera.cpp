#include "../../include/Components/Camera.h"

namespace YQ
{
	namespace OpenGL
	{
		const std::string YQ::Camera::GetName() const
		{
			return "camera";
		}

		void Camera::SetSize(float value)
		{
		}

		void Camera::SetNear(float value)
		{
			m_near = value;
		}

		void Camera::setFar(float value)
		{
			m_nfar = value;
		}

		void Camera::SetClearColor(const YQ::Vec3f& p_clearColor)
		{
		}

		const YQ::Matrix4f Camera::GetViweMatrix() const
		{
			return YQ::Math::LookAt(m_cameraPos, (m_cameraPos + m_cameraFront), m_wordUpUnit);
		}

		float Camera::GetScale() const
		{
			return m_zoom;
		}

		const YQ::Vec3f Camera::GetCurPos() const
		{
			return m_cameraPos;
		}

		const YQ::Vec3f Camera::GetFront() const
		{
			return m_cameraFront;
		}

		float Camera::GetNear() const
		{
			return m_near;
		}

		float Camera::GetFar() const
		{
			return m_nfar;
		}

		const YQ::Vec3f Camera::GetClearColor() const
		{
			return YQ::Vec3f();
		}

		void Camera::OnMovePos(Camera_Movement direction, float deltaTime)
		{
			float velocity = m_movementSpeed * deltaTime;

			switch (direction)
			{
			case Camera_Movement::eFORWARD:
				m_cameraPos += m_cameraFront * velocity;
				break;
			case Camera_Movement::eBACKWARD:
				m_cameraPos -= m_cameraFront * velocity;
				break;
			case Camera_Movement::eLEFT:
				m_cameraPos -= m_rightSelf * velocity;
				break;
			case Camera_Movement::eRIGHT:
				m_cameraPos += m_rightSelf * velocity;
				break;
			case Camera_Movement::eTop:
				m_cameraPos += YQ::Vec3f(0, 1, 0) * velocity;
				break;
			case Camera_Movement::eBottom:
				m_cameraPos -= YQ::Vec3f(0, 1, 0) * velocity;
				break;
			case Camera_Movement::eNone:
			default:
				break;
			}
		}

		void Camera::OnMoveView(float xOffset, float yOffset, bool constraint)
		{
			xOffset *= m_mouseSensitivity;
			yOffset *= m_mouseSensitivity;

			m_pitch += yOffset;
			m_yaw += xOffset;

			if (constraint)
			{
				if (m_pitch > 89.0f)
					m_pitch = 89.0f;
				else if (m_pitch < -89.0f)
					m_pitch = -89.0f;
			}

			UpdateSelfVec();
		}

		void Camera::OnZoomView(float yoffset)
		{
			m_zoom -= (float)yoffset;
			if (m_zoom < 1.0f)
				m_zoom = 1.0f;
			if (m_zoom > 45.0f)
				m_zoom = 45.0f;
		}

		void Camera::SetCameraPos(const YQ::Vec3f& pos)
		{
			m_cameraPos = pos;
		}

		void Camera::UpdateSelfVec()
		{
			YQ::Vec3f front;		//摄像机向前的向量
			front.SetValue(0, cos(YQ::Math::DegreesToRadians(m_yaw))
				* cos(YQ::Math::DegreesToRadians(m_pitch)));
			front.SetValue(1, sin(YQ::Math::DegreesToRadians(m_pitch)));
			front.SetValue(2, sin(YQ::Math::DegreesToRadians(m_yaw))
				* cos(YQ::Math::DegreesToRadians(m_pitch)));

			m_cameraFront = front.Normalization();

			m_rightSelf = YQ::Math::NormalVec(front, m_wordUpUnit);		//摄像机自身右向量

			m_upSelf = YQ::Math::NormalVec(front, m_rightSelf);
		}
	}
}
