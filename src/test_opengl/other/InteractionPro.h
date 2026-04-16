#pragma once
class Camera;
class GlWindow;

class InteractionPro
{
public:
	GlWindow* m_pWnd = nullptr;
	Camera* m_Camera = nullptr;
	float lastX = 400;
	float lastY = 300;

	double lastFrame = 0.0;
	double deltaTime = 0.0;


	void mouseMoveEvent(double xpos, double ypos);
	void keyKeyEnterEvent(int key, int scancode, int action, int mods);
	void updateDelta();
};

