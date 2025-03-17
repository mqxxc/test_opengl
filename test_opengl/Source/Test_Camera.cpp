#include "Test_Camera.h"
#include "Application.h"
#include "GlWindow.h"
#include "GlProgram.h"
#include "TextureUnit.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

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

	glm::mat4 model = glm::mat4(1.0f);

	glm::mat4 view;
	view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));

	glm::mat4 projection;
	projection = glm::perspective(glm::radians(45.0f), wnd->Width() / (float)wnd->Height(), 0.1f, 100.0f);

	glEnable(GL_DEPTH_TEST);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);	//摄像机位置
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);	//摄像机朝向
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);		//世界坐标中一个向上的向量

	float lastFrame = 0.0f;
	float deltaTime = 0.0f;

	std::function<void(int, int, int, int)> ketFun = [&](int key, int scancode, int action, int mods) {
		float cameraSpeed = 2.5f * deltaTime;
		switch (key)
		{
		case GLFW_KEY_W:
			cameraPos += cameraSpeed * cameraFront;
			break;
		case GLFW_KEY_S:
			cameraPos -= cameraSpeed * cameraFront;
		case GLFW_KEY_A:
			cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
			break;
		case GLFW_KEY_D:
			cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
			break;
		case GLFW_KEY_SPACE:
			wnd->Close();
			break;
		default:
			break;
		}
	};

	float lastX = 400, lastY = 300;
	float yaw = 0, pitch = 0;
	bool firstMouse = true;

	std::function<void(double, double)> mouseMove = [&](double xpos, double ypos){
		if (firstMouse)
		{
			lastX = xpos;
			lastY = ypos;
			firstMouse = false;
		}
		float xoffset = xpos - lastX;
		float yoffset = ypos - lastY;

		lastX = xpos;
		lastY = ypos;

		float sensitivity = 0.05f;

		yaw += xoffset * sensitivity;
		pitch += yoffset * sensitivity;

		if (pitch > 89.0f)
			pitch = 89.0f;
		else if (pitch < -89.0f)
			pitch = -89.0f;

		glm::vec3 front;
		front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
		front.y = sin(glm::radians(pitch));
		front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
		cameraFront = glm::normalize(front);
		int op = 1;
	};

	std::function<void()> fun = [&]() {
		//传入模型矩阵
		float curTime = static_cast<float>(glfwGetTime());
		deltaTime = curTime - lastFrame;
		lastFrame = curTime;

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		for (int i = 0; i < 10; ++i)
		{
			model = glm::rotate(glm::translate(glm::mat4(1.0f), cubePositions[i]), (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
			program->SetUniform("model", model);

			//传入观察矩阵
			view = glm::lookAt(cameraPos, (cameraPos + cameraFront), cameraUp);
			program->SetUniform("view", view);

			//传入投影矩阵
			program->SetUniform("projection", projection);

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
	};

	wnd->SetMouseMove(mouseMove);
	wnd->SetKeyEnter(ketFun);
	wnd->SetPrint(fun);
	app.Exec();

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	delete program;
	delete wnd;
}
