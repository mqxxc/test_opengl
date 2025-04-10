#include "Test_LightMapping.h"
#include "Application.h"
#include "GlWindow.h"
#include "GlProgram.h"
#include "Math.hpp"
#include "Camera.h"
#include "TextureUnit.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

void Test::Test_LightMapping()
{
	Application app;
	GlWindow* wnd = new GlWindow("LearnOpenGL", 800, 600);
	wnd->MakeContextCurrent();
	wnd->SetInputMode(GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	GlProgram* program = new GlProgram;
	program->CreateVertexShaderFromFile("resources/shader/LightMapping_block.vs");
	program->CreateFragmentShaderFromFile("resources/shader/LightMapping_block.fs");
	program->Complete();

	GlProgram* lightProgram = new GlProgram;
	lightProgram->CreateVertexShaderFromFile("resources/shader/Light_block_light.vs");
	lightProgram->CreateFragmentShaderFromFile("resources/shader/Light_block_light.fs");
	lightProgram->Complete();

	float vertices[] = {
		// positions          // normals           // texture coords
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
	};

	//顶点输入
	unsigned int VBO, VAO, VAO_light;

	//绑定顶点缓存
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);	//拷贝数据到顶点缓存中

	//顶点数组对象
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	//光源属性
	glGenVertexArrays(1, &VAO_light);
	glBindVertexArray(VAO_light);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glEnable(GL_DEPTH_TEST);		//开启深度测试

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

	YQ::Vec3f lightPos(1.2f, 1.0f, 2.0f);

	TextureUnit textur(GL_TEXTURE0);
	textur.LoadImg("resources/img/container2.png", true);
	textur.CreateGenerateMipmap();
	textur.SetRowAround(TextureUnit::eREPEAT);
	textur.SetColumnAround(TextureUnit::eREPEAT);
	textur.SetAmplifyStrategy(TextureUnit::eNEAREST);
	textur.SetShrinkStrategy(TextureUnit::eNEAREST);

	TextureUnit textur2(GL_TEXTURE1);
	textur2.LoadImg("resources/img/container2_specular.png", true);
	textur2.CreateGenerateMipmap();
	textur2.SetRowAround(TextureUnit::eREPEAT);
	textur2.SetColumnAround(TextureUnit::eREPEAT);
	textur2.SetAmplifyStrategy(TextureUnit::eNEAREST);
	textur2.SetShrinkStrategy(TextureUnit::eNEAREST);

	program->Use();
	program->SetUniform("lightColor", YQ::Vec3f(1.0f, 1.0f, 1.0f));
	program->SetUniform("lightPos", lightPos);
	program->SetTextureUnit(&textur, "material.diffuseMap");
	program->SetTextureUnit(&textur2, "material.specularMap");
	program->SetUniform("material.shininess", static_cast<float>(64.0f));

	program->SetUniform("light.ambient", YQ::Vec3f(0.2f, 0.2f, 0.2f));
	program->SetUniform("light.diffuse", YQ::Vec3f(0.5f, 0.5f, 0.5f));
	program->SetUniform("light.specular", YQ::Vec3f(1.0f, 1.0f, 1.0f));
	program->SetUniform("light.position", lightPos);
	

	std::function<void()> fun = [&]() {
		float curTime = static_cast<float>(glfwGetTime());
		deltaTime = curTime - lastFrame;
		lastFrame = curTime;

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//绘制物体
		program->Use();
		//传入模型矩阵
		YQ::Matrix4f model = YQ::Matrix4f::CreateOnce();
		program->SetUniform("model", model.Transposition());

		YQ::Matrix4f view = camera.GetViweMatrix();
		program->SetUniform("view", view.Transposition());

		YQ::Matrix4f projection = YQ::Math::CreaPerspective(YQ::Math::DegreesToRadians(camera.GetScale()),
			wnd->Width() / (float)wnd->Height(), 0.1f, 100.0f);
		program->SetUniform("projection", projection.Transposition());

		program->SetUniform("viewPos", camera.GetCurPos());
		textur.Build();
		textur2.Build();
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//绘制灯光
		lightProgram->Use();
		model = YQ::Matrix4f::CreateOnce();
		YQ::Math::Translate(model, lightPos);
		YQ::Math::Scale(model, YQ::Vec3f(0.6f, 0.6f, 0.6f));

		lightProgram->SetUniform("model", model.Transposition());

		lightProgram->SetUniform("view", view.Transposition());

		lightProgram->SetUniform("projection", projection.Transposition());
		glBindVertexArray(VAO_light);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	};

	wnd->SetMouseMove(mouseMove);
	wnd->SetKeyEnter(ketFun);
	wnd->SetPrint(fun);
	app.Exec();

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	delete program;
	delete lightProgram;
	delete wnd;
}
