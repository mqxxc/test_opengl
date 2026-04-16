#include "Test_FrameBuffer.h"
#include "Application.h"
#include "GlWindow.h"
#include "GlProgram.h"
#include "Camera.h"
#include "TextureUnit.h"
#include "VertexArray.h"
#include "StaticVertexBuffer.h"
#include "InteractionPro.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace Test
{
	void Text_FrameBuffer()
	{
		Application app;
		GlWindow* wnd = new GlWindow("LearnOpenGL", 800, 600);
		wnd->MakeContextCurrent();
		wnd->SetInputMode(GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		GlProgram* quadProgram = new GlProgram;
		quadProgram->CreateVertexShaderFromFile("resources/shader/FrameBuffer.vs");
		quadProgram->CreateFragmentShaderFromFile("resources/shader/FrameBuffer.fs");
		quadProgram->Complete();

		GlProgram* program = new GlProgram;
		program->CreateVertexShaderFromFile("resources/shader/DeepTesting.vs");
		program->CreateFragmentShaderFromFile("resources/shader/DeepTesting.fs");
		program->Complete();

		TextureUnit* floor = new TextureUnit(GL_TEXTURE0);
		floor->SetRowAround(TextureUnit::eREPEAT);
		floor->SetColumnAround(TextureUnit::eREPEAT);
		floor->SetAmplifyStrategy(TextureUnit::eNEAREST);
		floor->SetShrinkStrategy(TextureUnit::eNEAREST);
		floor->LoadImg("resources/img/floorTile.png", true);
		floor->CreateGenerateMipmap();

		TextureUnit* box = new TextureUnit(GL_TEXTURE1);
		box->SetRowAround(TextureUnit::eREPEAT);
		box->SetColumnAround(TextureUnit::eREPEAT);
		box->SetAmplifyStrategy(TextureUnit::eNEAREST);
		box->SetShrinkStrategy(TextureUnit::eNEAREST);
		box->LoadImg("resources/img/container.jpg");
		box->CreateGenerateMipmap();

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
			// positions          // texture Coords 
			 5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
			-5.0f, -0.5f,  5.0f,  0.0f, 0.0f,
			-5.0f, -0.5f, -5.0f,  0.0f, 2.0f,

			 5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
			-5.0f, -0.5f, -5.0f,  0.0f, 2.0f,
			 5.0f, -0.5f, -5.0f,  2.0f, 2.0f
		};
		float quadVertices[] = {
			// positions   // texCoords
			-1.0f,  1.0f,  0.0f, 1.0f,
			-1.0f, -1.0f,  0.0f, 0.0f,
			 1.0f, -1.0f,  1.0f, 0.0f,

			-1.0f,  1.0f,  0.0f, 1.0f,
			 1.0f, -1.0f,  1.0f, 0.0f,
			 1.0f,  1.0f,  1.0f, 1.0f
		};

		//箱子VAO
		StaticVertexBuffer boxVBO;
		boxVBO.CreateVBO(5);
		boxVBO.wirteData(cubeVertices, sizeof(cubeVertices) / sizeof(float));

		std::vector<VertexArray::VertexLayout> layout;
		layout.resize(2);
		layout[0].VBO = &boxVBO;
		layout[0].dataTypeEnum = GL_FLOAT;
		layout[0].offset = 0;
		layout[0].unitLength = sizeof(float);
		layout[0].attributeLength = 3;

		layout[1].VBO = &boxVBO;
		layout[1].dataTypeEnum = GL_FLOAT;
		layout[1].offset = 3;
		layout[1].unitLength = sizeof(float);
		layout[1].attributeLength = 2;

		VertexArray boxVAO;
		boxVAO.setupVBO(layout);

		//地板VAO
		StaticVertexBuffer planeVBO;
		planeVBO.CreateVBO(5);
		planeVBO.wirteData(planeVertices, sizeof(planeVertices) / sizeof(float));

		layout[0].VBO = &planeVBO;
		layout[0].dataTypeEnum = GL_FLOAT;
		layout[0].offset = 0;
		layout[0].unitLength = sizeof(float);
		layout[0].attributeLength = 3;

		layout[1].VBO = &planeVBO;
		layout[1].dataTypeEnum = GL_FLOAT;
		layout[1].offset = 3;
		layout[1].unitLength = sizeof(float);
		layout[1].attributeLength = 2;

		VertexArray planeVAO;
		planeVAO.setupVBO(layout);

		//四边形VAO
		StaticVertexBuffer quadVBO;
		quadVBO.CreateVBO(4);
		quadVBO.wirteData(quadVertices, sizeof(quadVertices) / sizeof(float));

		layout[0].VBO = &quadVBO;
		layout[0].dataTypeEnum = GL_FLOAT;
		layout[0].offset = 0;
		layout[0].unitLength = sizeof(float);
		layout[0].attributeLength = 2;

		layout[1].VBO = &quadVBO;
		layout[1].dataTypeEnum = GL_FLOAT;
		layout[1].offset = 2;
		layout[1].unitLength = sizeof(float);
		layout[1].attributeLength = 2;

		VertexArray quadVAO;
		quadVAO.setupVBO(layout);

		//帧缓冲对象
		uint framebuffer;
		glGenFramebuffers(1, &framebuffer);
		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

		uint textureColorbuffer;
		glGenTextures(1, &textureColorbuffer);
		glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, wnd->Width(), wnd->Height(), 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);

		uint depthRBO;
		glGenRenderbuffers(1, &depthRBO);
		glBindRenderbuffer(GL_RENDERBUFFER, depthRBO);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, wnd->Width(), wnd->Height());
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, depthRBO);
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		//摄像机
		Camera* camera = new Camera;
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
				direction = Camera::Camera_Movement::eTop;
				break;
			case GLFW_KEY_LEFT_CONTROL:
				direction = Camera::Camera_Movement::eBottom;
				break;
			case GLFW_KEY_ESCAPE:
				wnd->Close();
				break;
			default:
				break;
			}
			camera->OnMovePos(direction, cameraSpeed);
		};

		float lastX = 400, lastY = 300;
		float yaw = 0, pitch = 0;

		std::function<void(double, double)> mouseMove = [&](double xpos, double ypos) {
			camera->OnMoveView((float)xpos - lastX, (float)ypos - lastY);
			lastX = (float)xpos;
			lastY = (float)ypos;
		};

		camera->SetCameraPos({ 1.7f ,1.5f ,5.0f });
		camera->OnMoveView(0.0f, 120.0f);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		std::function<void()> fun = [&]() {
			float curTime = static_cast<float>(glfwGetTime());
			deltaTime = curTime - lastFrame;
			lastFrame = curTime;

			glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
			glEnable(GL_DEPTH_TEST);

			glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			program->Use();

			YQ::Matrix4f view = camera->GetViweMatrix();
			program->SetUniform("view", view.Transposition());

			YQ::Matrix4f projection = YQ::Math::CreaPerspective(YQ::Math::DegreesToRadians(camera->GetScale()),
				wnd->Width() / (float)wnd->Height(), 0.1f, 100.0f);
			program->SetUniform("projection", projection.Transposition());

			//绘制箱子
			boxVAO.bindVertexArray();
			box->Build();
			program->SetTextureUnit(box, "texture1");

			YQ::Matrix4f model = YQ::Matrix4f::CreateOnce();
			YQ::Math::Translate(model, YQ::Vec3(-1.0f, 0.0f, -1.0f));
			program->SetUniform("model", model.Transposition());
			glDrawArrays(GL_TRIANGLES, 0, 36);

			model = YQ::Matrix4f::CreateOnce();
			YQ::Math::Translate(model, YQ::Vec3(2.0f, 0.0f, 0.0f));
			program->SetUniform("model", model.Transposition());
			glDrawArrays(GL_TRIANGLES, 0, 36);

			//绘制地板
			planeVAO.bindVertexArray();
			model = YQ::Matrix4f::CreateOnce();
			program->SetUniform("model", model.Transposition());
			floor->Build();
			program->SetTextureUnit(floor, "texture1");
			glDrawArrays(GL_TRIANGLES, 0, 6);
			glBindVertexArray(0);

			//重新绑定窗口为绘制对象
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			glDisable(GL_DEPTH_TEST);

			glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			quadProgram->Use();
			quadVAO.bindVertexArray();
			glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
			glUniform1i(glGetUniformLocation(quadProgram->ProgramID(), "screenTexture"), 0);
			glDrawArrays(GL_TRIANGLES, 0, 6);
		};

		wnd->SetMouseMove(mouseMove);
		wnd->SetKeyEnter(ketFun);
		wnd->SetPrint(fun);
		app.Exec();

		delete program;
		delete quadProgram;
		delete floor;
		delete box;

		glDeleteRenderbuffers(1, &depthRBO);
		glDeleteFramebuffers(1, &framebuffer);
		delete wnd;
	}
}
