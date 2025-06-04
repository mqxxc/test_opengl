#include "Test_DeepTesting.h"
#include "TextureUnit.h"
#include "Application.h"
#include "GlWindow.h"
#include "GlProgram.h"
#include "Camera.h"
#include "Math.hpp"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace Test
{
	void Test_DeepTesting()
	{
		Application app;
		GlWindow* wnd = new GlWindow("LearnOpenGL", 800, 600);
		wnd->MakeContextCurrent();
		wnd->SetInputMode(GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		GlProgram* program = new GlProgram;
		program->CreateVertexShaderFromFile("resources/shader/DeepTesting.vs");
		program->CreateFragmentShaderFromFile("resources/shader/DeepTesting.fs");
		program->Complete();

		glEnable(GL_DEPTH_TEST);
		//glDepthFunc(GL_ALWAYS);

		float cubeVertices[] = {
			// positions          // texture Coords
			-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
			 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
			-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

			-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
			 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
		};

		float planeVertices[] = {
			// positions          
			 5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
			-5.0f, -0.5f,  5.0f,  0.0f, 0.0f,
			-5.0f, -0.5f, -5.0f,  0.0f, 2.0f,

			 5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
			-5.0f, -0.5f, -5.0f,  0.0f, 2.0f,
			 5.0f, -0.5f, -5.0f,  2.0f, 2.0f
		};

		uint groundVBO, groundVAO;
		glGenVertexArrays(1, &groundVAO);
		glGenBuffers(1, &groundVBO);

		glBindVertexArray(groundVAO);
		glBindBuffer(GL_ARRAY_BUFFER, groundVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), planeVertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		uint cubeVBO, cubeVAO;
		glGenVertexArrays(1, &cubeVAO);
		glGenBuffers(1, &cubeVBO);

		glBindVertexArray(cubeVAO);
		glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		Camera camera;
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
				wnd->Close();
				break;
			default:
				break;
			}
			camera.OnMovePos(direction, cameraSpeed);
		};

		float lastX = 400, lastY = 300;
		float yaw = 0, pitch = 0;

		std::function<void(double, double)> mouseMove = [&](double xpos, double ypos) {
			camera.OnMoveView(xpos - lastX, ypos - lastY);
			lastX = xpos;
			lastY = ypos;
		};

		camera.SetCameraPos({ 1.7f ,1.5f ,5.0f });
		camera.OnMoveView(0.0f, 120.0f);

		program->Use();

		TextureUnit floor(GL_TEXTURE0);
		floor.LoadImg("resources/img/floorTile.png",true);
		floor.SetRowAround(TextureUnit::eREPEAT);
		floor.SetColumnAround(TextureUnit::eREPEAT);
		floor.SetAmplifyStrategy(TextureUnit::eNEAREST);
		floor.SetShrinkStrategy(TextureUnit::eNEAREST);
		floor.CreateGenerateMipmap();

		TextureUnit cube(GL_TEXTURE1);
		cube.LoadImg("resources/img/marble.jpg", true);
		cube.SetRowAround(TextureUnit::eREPEAT);
		cube.SetColumnAround(TextureUnit::eREPEAT);
		cube.SetAmplifyStrategy(TextureUnit::eNEAREST);
		cube.SetShrinkStrategy(TextureUnit::eNEAREST);
		cube.CreateGenerateMipmap();

		std::function<void()> fun = [&]() {
			float curTime = static_cast<float>(glfwGetTime());
			deltaTime = curTime - lastFrame;
			lastFrame = curTime;

			glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			YQ::Matrix4f view = camera.GetViweMatrix();
			program->SetUniform("view", view.Transposition());

			YQ::Matrix4f projection = YQ::Math::CreaPerspective(YQ::Math::DegreesToRadians(camera.GetScale()),
				wnd->Width() / (float)wnd->Height(), 0.1f, 100.0f);
			program->SetUniform("projection", projection.Transposition());

			//立方体
			glBindVertexArray(cubeVAO);
			cube.Build();
			program->SetTextureUnit(&cube, "texture1");

			YQ::Matrix4f model = YQ::Matrix4f::CreateOnce();
			YQ::Math::Translate(model, YQ::Vec3f{ -1.0f, 0.0f, -1.0f });
			program->SetUniform("model", model.Transposition());
			glDrawArrays(GL_TRIANGLES, 0, 36);

			YQ::Math::Translate(model, YQ::Vec3f{ 2.0f, 2.0f, 0.0f });
			program->SetUniform("model", model.Transposition());
			glDrawArrays(GL_TRIANGLES, 0, 36);

			//绘制地板
			glBindVertexArray(groundVAO);
			model = YQ::Matrix4f::CreateOnce();
			program->SetUniform("model", model.Transposition());
			floor.Build();
			program->SetTextureUnit(&floor, "texture1");
			glDrawArrays(GL_TRIANGLES, 0, 6);
		};

		wnd->SetMouseMove(mouseMove);
		wnd->SetKeyEnter(ketFun);
		wnd->SetPrint(fun);
		app.Exec();

		delete program;
		delete wnd;
	}
}