#include "Test_TemplateTesting.h"
#include "TextureUnit.h"
#include "Application.h"
#include "GlWindow.h"
#include "GlProgram.h"
#include "Camera.h"
#include "YQMath.h"
#include "../Gl/StaticVertexBuffer.h"
#include "../Gl/VertexArray.h"
#include "InteractionPro.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

void Test::Test_TemplateTesting()
{
	Application app;
	GlWindow* wnd = new GlWindow("LearnOpenGL", 800, 600);
	wnd->MakeContextCurrent();
	wnd->SetInputMode(GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	GlProgram* program = new GlProgram;
	program->CreateVertexShaderFromFile("resources/shader/DeepTesting.vs");
	program->CreateFragmentShaderFromFile("resources/shader/DeepTesting.fs");
	program->Complete();

	GlProgram* edgeProgram = new GlProgram;
	edgeProgram->CreateVertexShaderFromFile("resources/shader/DeepTesting.vs");
	edgeProgram->CreateFragmentShaderFromFile("resources/shader/TemplateTesting/edge.fs");
	edgeProgram->Complete();

	glEnable(GL_STENCIL_TEST);

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

	StaticVertexBuffer groundVBO;
	groundVBO.CreateVBO(5);
	groundVBO.wirteData(planeVertices, sizeof(planeVertices) / sizeof(float));

	VertexArray groundVAO;
	std::vector<VertexArray::VertexLayout> groundLayoutList;
	groundLayoutList.resize(2);

	groundLayoutList[0].VBO = &groundVBO;
	groundLayoutList[0].dataTypeEnum = GL_FLOAT;
	groundLayoutList[0].offset = 0;
	groundLayoutList[0].unitLength = sizeof(float);
	groundLayoutList[0].attributeLength = 3;

	groundLayoutList[1].VBO = &groundVBO;
	groundLayoutList[1].dataTypeEnum = GL_FLOAT;
	groundLayoutList[1].offset = 3;
	groundLayoutList[1].unitLength = sizeof(float);
	groundLayoutList[1].attributeLength = 2;

	groundVAO.setupVBO(groundLayoutList);

	StaticVertexBuffer cubeVBO;
	cubeVBO.CreateVBO(5);
	cubeVBO.wirteData(cubeVertices, sizeof(cubeVertices) / sizeof(float));

	VertexArray cubeVAO;
	std::vector<VertexArray::VertexLayout> cubeLayoutList;
	cubeLayoutList.resize(2);

	cubeLayoutList[0].VBO = &cubeVBO;
	cubeLayoutList[0].dataTypeEnum = GL_FLOAT;
	cubeLayoutList[0].offset = 0;
	cubeLayoutList[0].unitLength = sizeof(float);
	cubeLayoutList[0].attributeLength = 3;

	cubeLayoutList[1].VBO = &cubeVBO;
	cubeLayoutList[1].dataTypeEnum = GL_FLOAT;
	cubeLayoutList[1].offset = 3;
	cubeLayoutList[1].unitLength = sizeof(float);
	cubeLayoutList[1].attributeLength = 2;

	cubeVAO.setupVBO(cubeLayoutList);

	Camera camera;
	camera.SetCameraPos({ 1.7f ,1.5f ,5.0f });
	camera.OnMoveView(0.0f, 120.0f);

	InteractionPro interactionPro;
	interactionPro.m_pWnd = wnd;
	interactionPro.m_Camera = &camera;

	TextureUnit floor(GL_TEXTURE0);
	floor.LoadImg("resources/img/floorTile.png", true);
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
		interactionPro.updateDelta();

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		program->Use();
		glEnable(GL_DEPTH_TEST);

		YQ::Matrix4f view = camera.GetViweMatrix();
		program->SetUniform("view", view.Transposition());

		YQ::Matrix4f projection = YQ::Math::CreaPerspective(YQ::Math::DegreesToRadians(camera.GetScale()),
			wnd->Width() / (float)wnd->Height(), 0.1f, 100.0f);
		program->SetUniform("projection", projection.Transposition());

		glStencilMask(0x00);
		//绘制地板
		groundVAO.bindVertexArray();
		YQ::Matrix4f model = YQ::Matrix4f::CreateOnce();
		program->SetUniform("model", model.Transposition());
		floor.Build();
		program->SetTextureUnit(&floor, "texture1");
		glDrawArrays(GL_TRIANGLES, 0, 6);

		glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
		glStencilFunc(GL_ALWAYS, 1, 0xFF);
		glStencilMask(0xFF);
		//立方体
		cubeVAO.bindVertexArray();
		cube.Build();
		program->SetTextureUnit(&cube, "texture1");

		model = YQ::Matrix4f::CreateOnce();
		YQ::Math::Translate(model, YQ::Vec3f{ -1.0f, 0.0f, -1.0f });
		program->SetUniform("model", model.Transposition());
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = YQ::Matrix4f::CreateOnce();
		YQ::Math::Translate(model, YQ::Vec3f{ 2.0f, 2.0f, 0.0f });
		program->SetUniform("model", model.Transposition());
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//绘制边框
		glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
		glDisable(GL_DEPTH_TEST);
		glStencilMask(0x00);
		edgeProgram->Use();
		edgeProgram->SetUniform("view", view.Transposition());
		edgeProgram->SetUniform("projection", projection.Transposition());

		cubeVAO.bindVertexArray();

		model = YQ::Matrix4f::CreateOnce();
		YQ::Math::Translate(model, YQ::Vec3f{ -1.0f, 0.0f, -1.0f });
		YQ::Math::Scale(model, YQ::Vec3f{ 1.1f, 1.1f, 1.1f });
		edgeProgram->SetUniform("model", model.Transposition());
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = YQ::Matrix4f::CreateOnce();
		YQ::Math::Translate(model, YQ::Vec3f{ 2.0f, 2.0f, 0.0f });
		YQ::Math::Scale(model, YQ::Vec3f{ 1.1f, 1.1f, 1.1f });
		edgeProgram->SetUniform("model", model.Transposition());
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glStencilMask(0xFF);		//仅当允许写入的时候，循环开始的清理模板缓冲才会生效
		glEnable(GL_DEPTH_TEST);
	};

	wnd->SetMouseMove([&interactionPro](double x, double y) {
		interactionPro.mouseMoveEvent(x, y);
	});

	wnd->SetKeyEnter([&interactionPro](int key, int scancode, int action, int mods) {
		interactionPro.keyKeyEnterEvent(key, scancode, action, mods);
	});

	wnd->SetPrint(fun);
	app.Exec();

	delete program;
	delete wnd;
}
