#include "InteractionPro.h"
#include "Camera.h"
#include "GlWindow.h"
#include "GLFW/glfw3.h"

constexpr double limitFPS = 1.0 / 144.0;

void InteractionPro::mouseMoveEvent(double xpos, double ypos)
{
	if (m_Camera != nullptr)
	{
		m_Camera->OnMoveView((float)xpos - lastX, (float)ypos - lastY);
		lastX = (float)xpos;
		lastY = (float)ypos;
	}
}

void InteractionPro::keyKeyEnterEvent(int key, int scancode, int action, int mods)
{
	float cameraSpeed = deltaTime;
	Camera::Camera_Movement direction = Camera::Camera_Movement::eNone;
	switch (key)
	{
	case GLFW_KEY_W:
		direction = Camera::Camera_Movement::eFORWARD;
		break;
	case GLFW_KEY_S:
		direction = Camera::Camera_Movement::eBACKWARD;
		break;
	case GLFW_KEY_A:
		direction = Camera::Camera_Movement::eLEFT;
		break;
	case GLFW_KEY_D:
		direction = Camera::Camera_Movement::eRIGHT;
		break;
	case GLFW_KEY_SPACE:
		direction = Camera::Camera_Movement::eTop;
		break;
	case GLFW_KEY_LEFT_CONTROL:
		direction = Camera::Camera_Movement::eBottom;
		break;
	case GLFW_KEY_ESCAPE:
		if (m_pWnd != nullptr)
		{
			m_pWnd->Close();
		}
		break;
	default:
		break;
	}

	if (m_Camera != nullptr
		&& direction != Camera::Camera_Movement::eNone)
	{
		m_Camera->OnMovePos(direction, cameraSpeed);
	}
}

void InteractionPro::updateDelta()
{
	double curTime = glfwGetTime();
	deltaTime += (curTime - lastFrame) / limitFPS;
	while (deltaTime >= 1.0)
	{
		--deltaTime;
	}
	lastFrame = curTime;
}
