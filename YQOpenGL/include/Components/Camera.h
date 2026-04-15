#pragma once
#include "../YQOpenGL_global.h"
#include <YQMath.h>

#include "ComponentBase.h"
#include "../Camera_Movement.h"

namespace YQ
{
	namespace OpenGL
	{
		class YQOpenGL_EXPORT Camera : public ComponentBase
		{
		public:
			Camera() = default;
			virtual ~Camera() = default;

			virtual const std::string GetName() const override;

			void SetSize(float value);			//透视投影：FOV视场角，正交投影：高度的一半
			void SetNear(float value);			//设置平截头近端参数
			void setFar(float value);			//设置平截头远端参数
			void SetClearColor(const YQ::Vec3f& p_clearColor);		//设置清理场景填充的颜色

			const YQ::Matrix4f GetViweMatrix() const;	//获取观察矩阵
			float GetScale() const;						//获取缩放值
			const YQ::Vec3f GetCurPos() const;			//获取摄像机位置
			const YQ::Vec3f GetFront() const;			//获取摄像机方向
			float GetNear() const;
			float GetFar() const;
			const YQ::Vec3f GetClearColor() const;


			void OnMovePos(Camera_Movement direction, float deltaTime);
			void OnMoveView(float xOffset, float yOffset, bool constraint = true);
			void OnZoomView(float yoffset);
			void SetCameraPos(const YQ::Vec3f& pos);

		private:
			//欧拉角，一般无滚转角
			float m_yaw = -90.0f;
			float m_pitch = 0.0f;

			//欧拉角限制
			float m_maxYaw = 89.0f;
			float m_maxPitch = 89.0f;

			//平截头
			float m_near = 0.1f;
			float m_nfar = 100.0f;

			float m_movementSpeed = 50.0f;		//移动速度
			float m_mouseSensitivity = 0.1f;	//鼠标灵敏度
			float m_zoom = 45.0f;				//缩放系数

			//YQ::Vec3f m_cameraPos = YQ::Vec3f(0.0f, 0.0f, 0.0f);
			YQ::Vec3f m_cameraPos = { 0.0f, 0.0f, 0.0f };
			YQ::Vec3f m_cameraFront = YQ::Vec3f(0.0f, 0.0f, -1.0f);
			YQ::Vec3f m_wordUpUnit = YQ::Vec3f(0.0f, 1.0f, 0.0f);
			YQ::Vec3f m_rightSelf;
			YQ::Vec3f m_upSelf;

			void UpdateSelfVec();
		};
	}
}

