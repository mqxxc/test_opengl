#include "Camera.h"

Camera::~Camera()
{
}

YQ::Matrix4f Camera::GetViweMatrix()
{
	return YQ::Math::LookAt(m_cameraPos, (m_cameraPos + m_cameraFront), m_wordUpUnit);
}

float Camera::GetScale()
{
	return m_zoom;
}

void Camera::OnMovePos(Camera_Movement direction, float deltaTime)
{
	float velocity = m_movementSpeed * deltaTime;

	switch (direction)
	{
	case Camera::Camera_Movement::eFORWARD:
		m_cameraPos += m_cameraFront * velocity;
		break;
	case Camera::Camera_Movement::eBACKWARD:
		m_cameraPos -= m_cameraFront * velocity;
		break;
	case Camera::Camera_Movement::eLEFT:
		m_cameraPos -= m_rightSelf * velocity;
		break;
	case Camera::Camera_Movement::eRIGHT:
		m_cameraPos += m_rightSelf * velocity;
		break;
	case Camera::Camera_Movement::eNone:
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
	YQ::Vec3f front;
	front.SetValue(0, cos(YQ::Math::DegreesToRadians(m_yaw))
		* cos(YQ::Math::DegreesToRadians(m_pitch)));
	front.SetValue(1, sin(YQ::Math::DegreesToRadians(m_pitch)));
	front.SetValue(2, sin(YQ::Math::DegreesToRadians(m_yaw))
		* cos(YQ::Math::DegreesToRadians(m_pitch)));

	m_cameraFront = front.Normalization();

	m_rightSelf = YQ::Math::NormalVec(front, m_wordUpUnit);

	m_upSelf = YQ::Math::NormalVec(front, m_rightSelf);
}
