#pragma once
#include "YQMath.h"

class Camera
{
public:
	enum class Camera_Movement
	{
		eNone,
		eFORWARD,
		eBACKWARD,
		eLEFT,
		eRIGHT,
		eTop,
		eBottom
	};

	Camera() = default;
	~Camera();

	YQ::Matrix4f GetViweMatrix();		//获取观察矩阵
	float GetScale();		//获取缩放值
	YQ::Vec3f GetCurPos();	//获取摄像机位置
	YQ::Vec3f GetFront();	//获取摄像机方向
	void OnMovePos(Camera_Movement direction, float deltaTime);
	void OnMoveView(float xOffset, float yOffset, bool constraint = true);
	void OnZoomView(float yoffset);
	void SetCameraPos(const YQ::Vec3f& pos);

private:
	//欧拉角
	float m_yaw = -90.0f;
	float m_pitch = 0.0f;

	float m_maxYaw = 89.0f;
	float m_maxPitch = 89.0f;

	float m_movementSpeed = 2.5f;		//移动速度
	float m_mouseSensitivity = 0.1f;	//鼠标灵敏度
	float m_zoom = 45.0f;				//缩放系数

	YQ::Vec3f m_cameraPos = YQ::Vec3f(0.0f, 0.0f, 0.0f);
	YQ::Vec3f m_cameraFront = YQ::Vec3f(0.0f, 0.0f, -1.0f);
	YQ::Vec3f m_wordUpUnit = YQ::Vec3f(0.0f, 1.0f, 0.0f);
	YQ::Vec3f m_rightSelf;
	YQ::Vec3f m_upSelf;

	void UpdateSelfVec();
};

