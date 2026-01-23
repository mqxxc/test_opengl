#include "Test_LoadModel.h"
#include "Application.h"
#include "GlWindow.h"
#include "GlProgram.h"
#include "YQMath.h"
#include "Camera.h"
#include "Model.h"
#include "StaticVertexBuffer.h"
#include "VertexArray.h"
#include "InteractionPro.h"

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

	float vertices[] = {
		-0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f, 
		 0.5f,  0.5f, -0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,

		-0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,

		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,

		 0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,

		-0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f, -0.5f,

		-0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
	};

	StaticVertexBuffer VBO;
	VBO.CreateVBO(3);
	VBO.wirteData(vertices, sizeof(vertices) / sizeof(float));

	std::vector<VertexArray::VertexLayout> layoutList;
	layoutList.resize(1);
	layoutList[0].VBO = &VBO;
	layoutList[0].dataTypeEnum = GL_FLOAT;
	layoutList[0].offset = 0;
	layoutList[0].unitLength = sizeof(float);
	layoutList[0].attributeLength = 3;
	
	VertexArray VAO;
	VAO.setupVBO(layoutList);

	Camera camera;
	camera.SetCameraPos({ 1.7f ,1.5f ,5.0f });
	camera.OnMoveView(0.0f, 120.0f);
	InteractionPro interactionPro;


	YQ::Vec3f lightPos(1.2f, 1.0f, 2.0f);

	YQ::Vec3f pointLightPosition(0.7f, 0.2f, 2.0f);
	Model backpack("resources/model/backpack/backpack.obj");

	program->Use();
	program->SetUniform("shininess", static_cast<float>(64.0f));

	// directional light
	program->SetUniform("dirLight.direction", YQ::Vec3f(-0.2f, -1.0f, -0.3f));
	program->SetUniform("dirLight.ambient", YQ::Vec3f(0.05f, 0.05f, 0.05f));
	program->SetUniform("dirLight.diffuse", YQ::Vec3f(0.4f, 0.4f, 0.4f));
	program->SetUniform("dirLight.specular", YQ::Vec3f(0.5f, 0.5f, 0.5f));
	// point light 
	program->SetUniform("pointLight.position", pointLightPosition);
	program->SetUniform("pointLight.ambient", YQ::Vec3f(0.05f, 0.05f, 0.05f));
	program->SetUniform("pointLight.diffuse", YQ::Vec3f(0.8f, 0.8f, 0.8f));
	program->SetUniform("pointLight.specular", YQ::Vec3f(1.0f, 1.0f, 1.0f));
	program->SetUniform("pointLight.constant", 1.0f);
	program->SetUniform("pointLight.linear", 0.09f);
	program->SetUniform("pointLight.quadratic", 0.032f);

	std::function<void()> fun = [&]() {
		interactionPro.updateDelta();

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
		program->SetUniform("viewPos", camera.GetCurPos());
		backpack.Draw(*program);

		//绘制灯光
		lightProgram->Use();
		lightProgram->SetUniform("view", view.Transposition());
		lightProgram->SetUniform("projection", projection.Transposition());
		VAO.bindVertexArray();

		model = YQ::Matrix4f::CreateOnce();
		YQ::Math::Translate(model, pointLightPosition);
		YQ::Math::Scale(model, YQ::Vec3f(0.2f, 0.2f, 0.2f));
		lightProgram->SetUniform("model", model.Transposition());

		glDrawArrays(GL_TRIANGLES, 0, 36);
	};

	wnd->SetMouseMove([&](double xpos, double ypos) {
		interactionPro.mouseMoveEvent(xpos, ypos);
		});
	wnd->SetKeyEnter([&](int key, int scancode, int action, int mods) {
		interactionPro.keyKeyEnterEvent(key, scancode, action, mods);
		});

	wnd->SetPrint(fun);
	app.Exec();

	delete program;
	delete lightProgram;
	delete wnd;
}
