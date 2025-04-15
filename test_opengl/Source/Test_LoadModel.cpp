#include "Test_LoadModel.h"
#include "Application.h"
#include "GlWindow.h"
#include "GlProgram.h"
#include "Math.hpp"
#include "Camera.h"
#include "Model.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "stb_image.h"

void Test::Test_LoadModel()
{
	Application app;
	GlWindow* wnd = new GlWindow("LearnOpenGL", 800, 600);
	wnd->MakeContextCurrent();
	wnd->SetInputMode(GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	GlProgram* program = new GlProgram;
	program->CreateVertexShaderFromFile("resources/shader/Loading_model.vs");
	program->CreateFragmentShaderFromFile("resources/shader/Loading_model.fs");
	program->Complete();

	GlProgram* lightProgram = new GlProgram;
	lightProgram->CreateVertexShaderFromFile("resources/shader/Light_block_light.vs");
	lightProgram->CreateFragmentShaderFromFile("resources/shader/Light_block_light.fs");
	lightProgram->Complete();

	//开启深度测试
	glEnable(GL_DEPTH_TEST);

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


	Model backpack("resources/model/backpack/backpack.obj");

	//program->Use();
	//program->SetUniform("lightColor", YQ::Vec3f(1.0f, 1.0f, 1.0f));
	//program->SetUniform("material.shininess", static_cast<float>(64.0f));

	//// directional light
	//program->SetUniform("dirLight.direction", YQ::Vec3f(-0.2f, -1.0f, -0.3f));
	//program->SetUniform("dirLight.ambient", YQ::Vec3f(0.05f, 0.05f, 0.05f));
	//program->SetUniform("dirLight.diffuse", YQ::Vec3f(0.4f, 0.4f, 0.4f));
	//program->SetUniform("dirLight.specular", YQ::Vec3f(0.5f, 0.5f, 0.5f));
	//// point light 1
	//program->SetUniform("pointLights[0].position", pointLightPositions[0]);
	//program->SetUniform("pointLights[0].ambient", YQ::Vec3f(0.05f, 0.05f, 0.05f));
	//program->SetUniform("pointLights[0].diffuse", YQ::Vec3f(0.8f, 0.8f, 0.8f));
	//program->SetUniform("pointLights[0].specular", YQ::Vec3f(1.0f, 1.0f, 1.0f));
	//program->SetUniform("pointLights[0].constant", 1.0f);
	//program->SetUniform("pointLights[0].linear", 0.09f);
	//program->SetUniform("pointLights[0].quadratic", 0.032f);
	//// point light 2
	//program->SetUniform("pointLights[1].position", pointLightPositions[1]);
	//program->SetUniform("pointLights[1].ambient", YQ::Vec3f(0.05f, 0.05f, 0.05f));
	//program->SetUniform("pointLights[1].diffuse", YQ::Vec3f(0.8f, 0.8f, 0.8f));
	//program->SetUniform("pointLights[1].specular", YQ::Vec3f(1.0f, 1.0f, 1.0f));
	//program->SetUniform("pointLights[1].constant", 1.0f);
	//program->SetUniform("pointLights[1].linear", 0.09f);
	//program->SetUniform("pointLights[1].quadratic", 0.032f);
	//// point light 3
	//program->SetUniform("pointLights[2].position", pointLightPositions[2]);
	//program->SetUniform("pointLights[2].ambient", YQ::Vec3f(0.05f, 0.05f, 0.05f));
	//program->SetUniform("pointLights[2].diffuse", YQ::Vec3f(0.8f, 0.8f, 0.8f));
	//program->SetUniform("pointLights[2].specular", YQ::Vec3f(1.0f, 1.0f, 1.0f));
	//program->SetUniform("pointLights[2].constant", 1.0f);
	//program->SetUniform("pointLights[2].linear", 0.09f);
	//program->SetUniform("pointLights[2].quadratic", 0.032f);
	//// point light 4
	//program->SetUniform("pointLights[3].position", pointLightPositions[3]);
	//program->SetUniform("pointLights[3].ambient", YQ::Vec3f(0.05f, 0.05f, 0.05f));
	//program->SetUniform("pointLights[3].diffuse", YQ::Vec3f(0.8f, 0.8f, 0.8f));
	//program->SetUniform("pointLights[3].specular", YQ::Vec3f(1.0f, 1.0f, 1.0f));
	//program->SetUniform("pointLights[3].constant", 1.0f);
	//program->SetUniform("pointLights[3].linear", 0.09f);
	//program->SetUniform("pointLights[3].quadratic", 0.032f);
	//// spotLight
	//program->SetUniform("spotLight.ambient", YQ::Vec3f(0.0f, 0.0f, 0.0f));
	//program->SetUniform("spotLight.diffuse", YQ::Vec3f(1.0f, 1.0f, 1.0f));
	//program->SetUniform("spotLight.specular", YQ::Vec3f(1.0f, 1.0f, 1.0f));
	//program->SetUniform("spotLight.constant", 1.0f);
	//program->SetUniform("spotLight.linear", 0.09f);
	//program->SetUniform("spotLight.quadratic", 0.032f);
	//program->SetUniform("spotLight.cutOff", cos(YQ::Math::DegreesToRadians(12.5f)));
	//program->SetUniform("spotLight.outerCutOff", cos(YQ::Math::DegreesToRadians(15.0f)));

	std::function<void()> fun = [&]() {
		float curTime = static_cast<float>(glfwGetTime());
		deltaTime = curTime - lastFrame;
		lastFrame = curTime;

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//绘制物体
		program->Use();
		
		YQ::Matrix4f model = YQ::Matrix4f::CreateOnce();
		program->SetUniform("model", model.Transposition());

		YQ::Matrix4f view = camera.GetViweMatrix();
		program->SetUniform("view", view.Transposition());

		YQ::Matrix4f projection = YQ::Math::CreaPerspective(YQ::Math::DegreesToRadians(camera.GetScale()),
			wnd->Width() / (float)wnd->Height(), 0.1f, 100.0f);
		program->SetUniform("projection", projection.Transposition());

		backpack.Draw(*program);

		/*program->SetUniform("viewPos", camera.GetCurPos());

		program->SetUniform("spotLight.position", camera.GetCurPos());
		program->SetUniform("spotLight.direction", camera.GetFront());*/

		//绘制灯光
		/*lightProgram->Use();
		lightProgram->SetUniform("view", view.Transposition());
		lightProgram->SetUniform("projection", projection.Transposition());
		glBindVertexArray(VAO_light);

		for (int i = 0; i < 4; ++i)
		{
			YQ::Matrix4f model = YQ::Matrix4f::CreateOnce();
			YQ::Math::Translate(model, pointLightPositions[i]);
			YQ::Math::Scale(model, YQ::Vec3f(0.2f, 0.2f, 0.2f));
			lightProgram->SetUniform("model", model.Transposition());

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}*/
	};

	wnd->SetMouseMove(mouseMove);
	wnd->SetKeyEnter(ketFun);
	wnd->SetPrint(fun);
	app.Exec();

	delete program;
	delete lightProgram;
	delete wnd;
}
