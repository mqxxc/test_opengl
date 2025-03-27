#pragma once
#include "Test_Camera.h"
#include "Application.h"
#include "GlWindow.h"
#include "GlProgram.h"
#include "TextureUnit.h"
#include "Math.hpp"
#include "Camera.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

void Test::Test_Camera()
{
	Application app;
	GlWindow* wnd = new GlWindow("LearnOpenGL", 800, 600);
	wnd->MakeContextCurrent();
	wnd->SetInputMode(GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	GlProgram* program = new GlProgram;
	program->CreateVertexShaderFromFile("src/shader/CoordinateSystem.vs");
	program->CreateFragmentShaderFromFile("src/shader/CoordinateSystem.fs");
	program->Complete();

	float vertices[] = {
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

	//顶点输入
	unsigned int VBO, VAO;

	//绑定顶点缓存
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);	//拷贝数据到顶点缓存中

	//顶点数组对象
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);//启用顶点属性
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);//启用顶点属性

	TextureUnit texture1(GL_TEXTURE0);
	texture1.SetRowAround(TextureUnit::eREPEAT);
	texture1.SetColumnAround(TextureUnit::eREPEAT);
	texture1.SetAmplifyStrategy(TextureUnit::eNEAREST);
	texture1.SetShrinkStrategy(TextureUnit::eNEAREST);
	texture1.LoadImg("src/img/container.jpg");
	texture1.CreateGenerateMipmap();

	TextureUnit texture2(GL_TEXTURE1);
	texture2.SetRowAround(TextureUnit::eREPEAT);
	texture2.SetColumnAround(TextureUnit::eREPEAT);
	texture2.SetAmplifyStrategy(TextureUnit::eNEAREST);
	texture2.SetShrinkStrategy(TextureUnit::eNEAREST);
	texture2.LoadImg("src/img/awesomeface.png", true);
	texture2.CreateGenerateMipmap();

	program->Use();

	program->SetTextureUnit(&texture1, "Texture1");
	program->SetTextureUnit(&texture2, "Texture2");

	glEnable(GL_DEPTH_TEST);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

	YQ::Vec<float, 3> cubePositions[] = {
		YQ::Vec<float, 3>(0.0f,  0.0f,  0.0f),
		YQ::Vec<float, 3>(2.0f,  5.0f, -15.0f),
		YQ::Vec<float, 3>(-1.5f, -2.2f, -2.5f),
		YQ::Vec<float, 3>(-3.8f, -2.0f, -12.3f),
		YQ::Vec<float, 3>(2.4f, -0.4f, -3.5f),
		YQ::Vec<float, 3>(-1.7f,  3.0f, -7.5f),
		YQ::Vec<float, 3>(1.3f, -2.0f, -2.5f),
		YQ::Vec<float, 3>(1.5f,  2.0f, -2.5f),
		YQ::Vec<float, 3>(1.5f,  0.2f, -1.5f),
		YQ::Vec<float, 3>(-1.3f,  1.0f, -1.5f)
	};

	float lastFrame = 0.0f;
	float deltaTime = 0.0f;
	Camera camera;

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

	std::function<void(double, double)> mouseMove = [&](double xpos, double ypos){
		camera.OnMoveView(xpos - lastX, ypos - lastY);
		lastX = xpos;
		lastY = ypos;
	};

	std::function<void(double, double)> wheel = [&](double xpos, double ypos) {
		camera.OnZoomView(ypos);
	};

	YQ::Matrix4f model = YQ::Matrix4f::CreateOnce();

	YQ::Matrix4f projection = YQ::Matrix4f::CreateOnce();

	std::function<void()> fun = [&]() {
		float curTime = static_cast<float>(glfwGetTime());
		deltaTime = curTime - lastFrame;
		lastFrame = curTime;
		
		//传入观察矩阵
		YQ::Matrix4f view = camera.GetViweMatrix();
		program->SetUniform("view", view.Transposition());

		//传入投影矩阵
		projection = YQ::Math::CreaPerspective(YQ::Math::DegreesToRadians(camera.GetScale()),
			wnd->Width() / (float)wnd->Height(), 0.1f, 100.0f);
		program->SetUniform("projection", projection.Transposition());

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		for (int i = 0; i < 10; ++i)
		{
			//传入模型矩阵
			model = YQ::Matrix4f::CreateOnce();
			YQ::Math::Translate(model, cubePositions[i]);
			model = YQ::Math::Rotate(model,
				(float)glfwGetTime() * YQ::Math::DegreesToRadians(50.0f), YQ::Vec<float, 3>(0.5f, 1.0f, 0.0f));
			program->SetUniform("model", model.Transposition());

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
	};

	wnd->SetMouseMove(mouseMove);
	wnd->SetKeyEnter(ketFun);
	wnd->SetPrint(fun);
	wnd->SetWheel(wheel);
	app.Exec();

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	delete program;
	delete wnd;
}
