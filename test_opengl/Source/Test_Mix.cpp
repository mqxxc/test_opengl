#include "Test_Mix.h"
#include "TextureUnit.h"
#include "Application.h"
#include "Glwindow.h"
#include "GlProgram.h"
#include "Camera.h"
#include "YQMath.h"
#include "StaticVertexBuffer.h"
#include "VertexArray.h"
#include "InteractionPro.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

void Test::Test_Mix()
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
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);		//设置混合函数

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
		// positions          //texture Coords
		 5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
		-5.0f, -0.5f,  5.0f,  0.0f, 0.0f,
		-5.0f, -0.5f, -5.0f,  0.0f, 2.0f,

		 5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
		-5.0f, -0.5f, -5.0f,  0.0f, 2.0f,
		 5.0f, -0.5f, -5.0f,  2.0f, 2.0f
	};

	float windowVertices[] = {
		// positions         //texture Coords
		0.0f,  0.5f,  0.6f,  0.0f,  0.0f,
		0.0f, -0.5f,  0.6f,  0.0f,  1.0f,
		1.0f, -0.5f,  0.6f,  1.0f,  1.0f,

		0.0f,  0.5f,  0.6f,  0.0f,  0.0f,
		1.0f, -0.5f,  0.6f,  1.0f,  1.0f,
		1.0f,  0.5f,  0.6f,  1.0f,  0.0f
	};

	StaticVertexBuffer groundVBO;
	groundVBO.CreateVBO(5);
	groundVBO.wirteData(planeVertices, sizeof(planeVertices) / sizeof(float));

	StaticVertexBuffer cubeVBO;
	cubeVBO.CreateVBO(5);
	cubeVBO.wirteData(cubeVertices, sizeof(cubeVertices) / sizeof(float));

	StaticVertexBuffer windowVBO;
	windowVBO.CreateVBO(5);
	windowVBO.wirteData(windowVertices, sizeof(windowVertices) / sizeof(float));

	VertexArray groundVAO;
	std::vector<VertexArray::VertexLayout> LayoutList;
	LayoutList.resize(2);
	LayoutList[0].VBO = &groundVBO;
	LayoutList[0].dataTypeEnum = GL_FLOAT;
	LayoutList[0].offset = 0;
	LayoutList[0].unitLength = sizeof(float);
	LayoutList[0].attributeLength = 3;

	LayoutList[1].VBO = &groundVBO;
	LayoutList[1].dataTypeEnum = GL_FLOAT;
	LayoutList[1].offset = 3;
	LayoutList[1].unitLength = sizeof(float);
	LayoutList[1].attributeLength = 2;
	groundVAO.setupVBO(LayoutList);

	VertexArray cubeVAO;
	LayoutList[0].VBO = &cubeVBO;
	LayoutList[1].VBO = &cubeVBO;
	cubeVAO.setupVBO(LayoutList);

	VertexArray windowVAO;
	LayoutList[0].VBO = &windowVBO;
	LayoutList[1].VBO = &windowVBO;
	windowVAO.setupVBO(LayoutList);
	
	Camera* camera = new Camera;
	camera->SetCameraPos({ 1.7f ,1.5f ,5.0f });
	camera->OnMoveView(0.0f, 120.0f);

	InteractionPro interactionPro;
	interactionPro.m_pWnd = wnd;
	interactionPro.m_Camera = camera;

	TextureUnit* floor = new TextureUnit(GL_TEXTURE0);
	floor->LoadImg("resources/img/floorTile.png", true);
	floor->SetRowAround(TextureUnit::eREPEAT);
	floor->SetColumnAround(TextureUnit::eREPEAT);
	floor->SetAmplifyStrategy(TextureUnit::eNEAREST);
	floor->SetShrinkStrategy(TextureUnit::eNEAREST);
	floor->CreateGenerateMipmap();

	TextureUnit* cube = new TextureUnit(GL_TEXTURE1);
	cube->LoadImg("resources/img/marble.jpg", true);
	cube->SetRowAround(TextureUnit::eREPEAT);
	cube->SetColumnAround(TextureUnit::eREPEAT);
	cube->SetAmplifyStrategy(TextureUnit::eNEAREST);
	cube->SetShrinkStrategy(TextureUnit::eNEAREST);
	cube->CreateGenerateMipmap();

	TextureUnit* window = new TextureUnit(GL_TEXTURE2);
	window->LoadImg("resources/img/window.png", true);
	window->SetRowAround(TextureUnit::eREPEAT);
	window->SetColumnAround(TextureUnit::eREPEAT);
	window->SetAmplifyStrategy(TextureUnit::eNEAREST);
	window->SetShrinkStrategy(TextureUnit::eNEAREST);
	window->CreateGenerateMipmap();

	std::function<void()> fun = [&]() {
		interactionPro.updateDelta();

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
		groundVAO.bindVertexArray();
		YQ::Matrix4f model = YQ::Matrix4f::CreateOnce();
		program->SetUniform("model", model.Transposition());
		floor->Build();
		program->SetTextureUnit(floor, "texture1");
		glDrawArrays(GL_TRIANGLES, 0, 6);

		glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
		glStencilFunc(GL_ALWAYS, 1, 0xFF);
		glStencilMask(0xFF);
		//立方体
		cubeVAO.bindVertexArray();
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
		windowVAO.bindVertexArray();
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

	wnd->SetMouseMove([&](double xpos, double ypos) {
		interactionPro.mouseMoveEvent(xpos, ypos);
		});
	wnd->SetKeyEnter([&](int key, int scancode, int action, int mods) {
		interactionPro.keyKeyEnterEvent(key, scancode, action, mods);
		});
	wnd->SetPrint(fun);
	app.Exec();

	delete program;
	delete wnd;
}

