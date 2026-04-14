#include "Test_DeepTesting.h"
#include "TextureUnit.h"
#include "Application.h"
#include "GlWindow.h"
#include "GlProgram.h"
#include "Camera.h"
#include "YQMath.h"
#include "StaticVertexBuffer.h"
#include "VertexArray.h"
#include "InteractionPro.h"

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

		StaticVertexBuffer groundVBO;
		groundVBO.CreateVBO(5);
		groundVBO.wirteData(planeVertices, sizeof(planeVertices) / sizeof(float));

		std::vector<VertexArray::VertexLayout> groundLayout;
		groundLayout.resize(2);
		groundLayout[0].VBO = &groundVBO;
		groundLayout[0].dataTypeEnum = GL_FLOAT;
		groundLayout[0].offset = 0;
		groundLayout[0].unitLength = sizeof(float);
		groundLayout[0].attributeLength = 3;

		groundLayout[1].VBO = &groundVBO;
		groundLayout[1].dataTypeEnum = GL_FLOAT;
		groundLayout[1].offset = 3;
		groundLayout[1].unitLength = sizeof(float);
		groundLayout[1].attributeLength = 2;

		VertexArray groundVAO;
		groundVAO.setupVBO(groundLayout);


		StaticVertexBuffer cubeVBO;
		cubeVBO.CreateVBO(5);
		cubeVBO.wirteData(cubeVertices, sizeof(cubeVertices) / sizeof(float));

		groundLayout[0].VBO = &cubeVBO;
		groundLayout[1].VBO = &cubeVBO;
		VertexArray cubeVAO;
		cubeVAO.setupVBO(groundLayout);

		Camera camera;
		camera.SetCameraPos({ 1.7f ,1.5f ,5.0f });
		camera.OnMoveView(0.0f, 120.0f);
		InteractionPro interactionPro;
		interactionPro.m_pWnd = wnd;
		interactionPro.m_Camera = &camera;

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
			interactionPro.updateDelta();

			glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			YQ::Matrix4f view = camera.GetViweMatrix();
			program->SetUniform("view", view.Transposition());

			YQ::Matrix4f projection = YQ::Math::CreaPerspective(YQ::Math::DegreesToRadians(camera.GetScale()),
				wnd->Width() / (float)wnd->Height(), 0.1f, 100.0f);
			program->SetUniform("projection", projection.Transposition());

			//立方体
			cubeVAO.bindVertexArray();
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
			groundVAO.bindVertexArray();
			model = YQ::Matrix4f::CreateOnce();
			program->SetUniform("model", model.Transposition());
			floor.Build();
			program->SetTextureUnit(&floor, "texture1");
			glDrawArrays(GL_TRIANGLES, 0, 6);
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
}