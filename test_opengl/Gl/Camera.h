#pragma once
#include "Math.hpp"

class Camera
{
public:
	enum class Camera_Movement
	{
		eNone,
		eFORWARD,
		eBACKWARD,
		eLEFT,
		eRIGHT
	};

	Camera() = default;
	~Camera();

	YQ::Matrix4f GetViweMatrix();		//��ȡ�۲����
	float GetScale();		//��ȡ����ֵ
	YQ::Vec3f GetCurPos();	//��ȡ�����λ��
	YQ::Vec3f GetFront();	//��ȡ���������
	void OnMovePos(Camera_Movement direction, float deltaTime);
	void OnMoveView(float xOffset, float yOffset, bool constraint = true);
	void OnZoomView(float yoffset);
	void SetCameraPos(const YQ::Vec3f& pos);

private:
	//ŷ����
	float m_yaw = -90.0f;
	float m_pitch = 0.0f;

	float m_maxYaw = 89.0f;
	float m_maxPitch = 89.0f;

	float m_movementSpeed = 2.5f;		//�ƶ��ٶ�
	float m_mouseSensitivity = 0.1f;	//���������
	float m_zoom = 45.0f;				//����ϵ��

	YQ::Vec3f m_cameraPos = YQ::Vec3f(0.0f, 0.0f, 0.0f);
	YQ::Vec3f m_cameraFront = YQ::Vec3f(0.0f, 0.0f, -1.0f);
	YQ::Vec3f m_wordUpUnit = YQ::Vec3f(0.0f, 1.0f, 0.0f);
	YQ::Vec3f m_rightSelf;
	YQ::Vec3f m_upSelf;

	void UpdateSelfVec();
};

