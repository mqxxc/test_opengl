#include "Test_Light.h"
#include "Application.h"
#include "GlWindow.h"
#include "GlProgram.h"
#include "YQMath.h"
#include "Camera.h"
#include "StaticVertexBuffer.h"
#include "VertexArray.h"
#include "InteractionPro.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

void Test::Test_Light()
{
	Application app;
	GlWindow* wnd = new GlWindow("LearnOpenGL", 800, 600);
	wnd->MakeContextCurrent();
	wnd->SetInputMode(GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	GlProgram* program = new GlProgram;
	program->CreateVertexShaderFromFile("resources/shader/Light_block.vs");
	program->CreateFragmentShaderFromFile("resources/shader/Light_block.fs");
	program->Complete();

	GlProgram* lightProgram = new GlProgram;
	lightProgram->CreateVertexShaderFromFile("resources/shader/Light_block_light.vs");
	lightProgram->CreateFragmentShaderFromFile("resources/shader/Light_block_light.fs");
	lightProgram->Complete();

	float vertices[] = {
	-0.5f,-0.5f,  -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
	};

	StaticVertexBuffer VBO;
	VBO.CreateVBO(6);
	VBO.wirteData(vertices, sizeof(vertices) / sizeof(float));

	std::vector<VertexArray::VertexLayout> layoutList;
	layoutList.resize(2);
	layoutList[0].VBO = &VBO;
	layoutList[0].dataTypeEnum = GL_FLOAT;
	layoutList[0].offset = 0;
	layoutList[0].unitLength = sizeof(float);
	layoutList[0].attributeLength = 3;

	layoutList[1].VBO = &VBO;
	layoutList[1].dataTypeEnum = GL_FLOAT;
	layoutList[1].offset = 3;
	layoutList[1].unitLength = sizeof(float);
	layoutList[1].attributeLength = 3;

	VertexArray VAO;
	VAO.setupVBO(layoutList);

	VertexArray VAO_light;
	std::vector<VertexArray::VertexLayout> lightLayoutList;
	lightLayoutList.resize(1);
	lightLayoutList[0].VBO = &VBO;
	lightLayoutList[0].dataTypeEnum = GL_FLOAT;
	lightLayoutList[0].offset = 0;
	lightLayoutList[0].unitLength = sizeof(float);
	lightLayoutList[0].attributeLength = 3;
	VAO_light.setupVBO(lightLayoutList);

	glEnable(GL_DEPTH_TEST);		//开启深度测试

	Camera camera;
	camera.SetCameraPos({ 1.7f ,1.5f ,5.0f });
	camera.OnMoveView(0.0f, 120.0f);

	InteractionPro interactionPro;
	interactionPro.m_pWnd = wnd;
	interactionPro.m_Camera = &camera;

	YQ::Vec3f lightPos(1.2f, 1.0f, 2.0f);

	program->Use();
	program->SetUniform("objColor", YQ::Vec3f(1.0f, 0.5f, 0.31f));
	program->SetUniform("lightColor", YQ::Vec3f(1.0f, 1.0f, 1.0f));
	program->SetUniform("lightPos", lightPos);
	

	std::function<void()> fun = [&]() {
		interactionPro.updateDelta();

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
		VAO.bindVertexArray();
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//绘制灯光
		lightProgram->Use();
		model = YQ::Matrix4f::CreateOnce();
		YQ::Math::Translate(model, lightPos);
		YQ::Math::Scale(model, YQ::Vec3f(0.6f, 0.6f, 0.6f));

		lightProgram->SetUniform("model", model.Transposition());

		lightProgram->SetUniform("view", view.Transposition());

		lightProgram->SetUniform("projection", projection.Transposition());
		VAO_light.bindVertexArray();
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
