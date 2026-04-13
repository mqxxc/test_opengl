#include "Test_FrameBuffer.h"
#include "Application.h"
#include "GlWindow.h"
#include "GlProgram.h"
#include "Camera.h"
#include "TextureUnit.h"
#include "VertexArray.h"
#include "StaticVertexBuffer.h"
#include "InteractionPro.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace Test
{
	void Text_FrameBuffer()
	{
		Application app;
		GlWindow* wnd = new GlWindow("LearnOpenGL", 800, 600);
		wnd->MakeContextCurrent();
		wnd->SetInputMode(GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		GlProgram* program = new GlProgram;
		program->CreateVertexShaderFromFile("resources/shader/DeepTesting.vs");
		program->CreateFragmentShaderFromFile("resources/shader/DeepTesting.fs");
		program->Complete();


		Camera* camera = new Camera;
		float lastFrame = 0.0f;
		float deltaTime = 0.0f;

		std::function<void(int, int, int, int)> ketFun = [&](int key, int scancode, int action, int mods) {
			float cameraSpeed = 2.5f * deltaTime;
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
				wnd->Close();
				break;
			default:
				break;
			}
			camera->OnMovePos(direction, cameraSpeed);
		};

		float lastX = 400, lastY = 300;
		float yaw = 0, pitch = 0;

		std::function<void(double, double)> mouseMove = [&](double xpos, double ypos) {
			camera->OnMoveView((float)xpos - lastX, (float)ypos - lastY);
			lastX = xpos;
			lastY = ypos;
		};

		camera->SetCameraPos({ 1.7f ,1.5f ,5.0f });
		camera->OnMoveView(0.0f, 120.0f);

		TextureUnit* floor = new TextureUnit(GL_TEXTURE0);
		floor->LoadImg("resources/img/floorTile.png", true);
		floor->SetRowAround(TextureUnit::eREPEAT);
		floor->SetColumnAround(TextureUnit::eREPEAT);
		floor->SetAmplifyStrategy(TextureUnit::eNEAREST);
		floor->SetShrinkStrategy(TextureUnit::eNEAREST);
		floor->CreateGenerateMipmap();

		TextureUnit* box = new TextureUnit(GL_TEXTURE1);
		box->LoadImg("resources/img/container.jpg", true);
		box->SetRowAround(TextureUnit::eREPEAT);
		box->SetColumnAround(TextureUnit::eREPEAT);
		box->SetAmplifyStrategy(TextureUnit::eNEAREST);
		box->SetShrinkStrategy(TextureUnit::eNEAREST);
		box->CreateGenerateMipmap();

		std::function<void()> fun = [&]() {
			float curTime = static_cast<float>(glfwGetTime());
			deltaTime = curTime - lastFrame;
			lastFrame = curTime;

			glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

			program->Use();


			YQ::Matrix4f view = camera->GetViweMatrix();
			program->SetUniform("view", view.Transposition());

			YQ::Matrix4f projection = YQ::Math::CreaPerspective(YQ::Math::DegreesToRadians(camera->GetScale()),
				wnd->Width() / (float)wnd->Height(), 0.1f, 100.0f);
			program->SetUniform("projection", projection.Transposition());

			glStencilMask(0x00);
			//绘制地板
			glBindVertexArray(groundVAO);
			YQ::Matrix4f model = YQ::Matrix4f::CreateOnce();
			program->SetUniform("model", model.Transposition());
			floor->Build();
			program->SetTextureUnit(floor, "texture1");
			glDrawArrays(GL_TRIANGLES, 0, 6);

			glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
			glStencilFunc(GL_ALWAYS, 1, 0xFF);
			glStencilMask(0xFF);
			//立方体
			glBindVertexArray(cubeVAO);
			cube->Build();
			program->SetTextureUnit(cube, "texture1");

			model = YQ::Matrix4f::CreateOnce();
			YQ::Math::Translate(model, YQ::Vec3f{ -1.0f, 0.0f, -1.0f });
			program->SetUniform("model", model.Transposition());
			glDrawArrays(GL_TRIANGLES, 0, 36);

			model = YQ::Matrix4f::CreateOnce();
			YQ::Math::Translate(model, YQ::Vec3f{ 2.0f, 0.0f, 0.0f });
			program->SetUniform("model", model.Transposition());
			glDrawArrays(GL_TRIANGLES, 0, 36);

			//绘制透明窗户（如果想要是实现镜头移动也能正常渲染半透明物体时需要再循环中进行排序或者使用顺序无关的渲染算法）
			glBindVertexArray(windowVAO);
			window->Build();
			program->SetTextureUnit(window, "texture1");

			model = YQ::Matrix4f::CreateOnce();
			YQ::Math::Translate(model, YQ::Vec3f{ -0.5f, 0.0f, -2.0f });
			program->SetUniform("model", model.Transposition());
			glDrawArrays(GL_TRIANGLES, 0, 36);

			model = YQ::Matrix4f::CreateOnce();
			YQ::Math::Translate(model, YQ::Vec3f{ 0.5f, 0.0f, -1.0f });
			program->SetUniform("model", model.Transposition());
			glDrawArrays(GL_TRIANGLES, 0, 36);

			model = YQ::Matrix4f::CreateOnce();
			YQ::Math::Translate(model, YQ::Vec3f{ -1.5f, 0.0f, -1.0f });
			program->SetUniform("model", model.Transposition());
			glDrawArrays(GL_TRIANGLES, 0, 36);

			model = YQ::Matrix4f::CreateOnce();
			YQ::Math::Translate(model, YQ::Vec3f{ 1.5f, 0.0f, 0.0f });
			program->SetUniform("model", model.Transposition());
			glDrawArrays(GL_TRIANGLES, 0, 36);

			model = YQ::Matrix4f::CreateOnce();
			YQ::Math::Translate(model, YQ::Vec3f{ 0.0f, 0.0f, 0.0f });
			program->SetUniform("model", model.Transposition());
			glDrawArrays(GL_TRIANGLES, 0, 36);

		};

		wnd->SetMouseMove(mouseMove);
		wnd->SetKeyEnter(ketFun);
		wnd->SetPrint(fun);
		app.Exec();

		delete program;
		delete wnd;
	}
}
