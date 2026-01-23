#include "Test_LightSources.h"
#include "Application.h"
#include "GlWindow.h"
#include "GlProgram.h"
#include "YQMath.h"
#include "Camera.h"
#include "TextureUnit.h"
#include "StaticVertexBuffer.h"
#include "VertexArray.h"
#include "InteractionPro.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

void Test::Test_LightSources()
{
	Application app;
	GlWindow* wnd = new GlWindow("LearnOpenGL", 800, 600);
	wnd->MakeContextCurrent();
	wnd->SetInputMode(GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	GlProgram* program = new GlProgram;
	program->CreateVertexShaderFromFile("resources/shader/LightSources.vs");
	program->CreateFragmentShaderFromFile("resources/shader/LightSources.fs");
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

	//绘制多个物体时的偏移量
	YQ::Vec3f cubePositions[] = {
		YQ::Vec3f(0.0f,  0.0f,  0.0f),
		YQ::Vec3f(2.0f,  5.0f, -15.0f),
		YQ::Vec3f(-1.5f, -2.2f, -2.5f),
		YQ::Vec3f(-3.8f, -2.0f, -12.3f),
		YQ::Vec3f(2.4f, -0.4f, -3.5f),
		YQ::Vec3f(-1.7f,  3.0f, -7.5f),
		YQ::Vec3f(1.3f, -2.0f, -2.5f),
		YQ::Vec3f(1.5f,  2.0f, -2.5f),
		YQ::Vec3f(1.5f,  0.2f, -1.5f),
		YQ::Vec3f(-1.3f,  1.0f, -1.5f)
	};

	//绘制多个点光源的偏移量
	YQ::Vec3f pointLightPositions[] = {
		YQ::Vec3f(0.7f,  0.2f,  2.0f),
		YQ::Vec3f(2.3f, -3.3f, -4.0f),
		YQ::Vec3f(-4.0f,  2.0f, -12.0f),
		YQ::Vec3f(0.0f,  0.0f, -3.0f)
	};

	StaticVertexBuffer VBO;
	VBO.CreateVBO(8);
	VBO.wirteData(vertices, sizeof(vertices) / sizeof(float));

	VertexArray VAO;
	std::vector<VertexArray::VertexLayout> layoutList;
	layoutList.resize(3);
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

	layoutList[2].VBO = &VBO;
	layoutList[2].dataTypeEnum = GL_FLOAT;
	layoutList[2].offset = 6;
	layoutList[2].unitLength = sizeof(float);
	layoutList[2].attributeLength = 2;
	VAO.setupVBO(layoutList);

	VertexArray VAO_light;
	VAO_light.setupVBO(layoutList);

	//开启深度测试
	glEnable(GL_DEPTH_TEST);		

	Camera camera;
	camera.SetCameraPos({ 1.7f ,1.5f ,5.0f });
	camera.OnMoveView(0.0f, 120.0f);

	InteractionPro interactionPro;
	interactionPro.m_pWnd = wnd;
	interactionPro.m_Camera = &camera;

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
	program->SetTextureUnit(&textur, "material.diffuseMap");
	program->SetTextureUnit(&textur2, "material.specularMap");
	program->SetUniform("material.shininess", static_cast<float>(64.0f));

	// directional light
	program->SetUniform("dirLight.direction", YQ::Vec3f(-0.2f, -1.0f, -0.3f));
	program->SetUniform("dirLight.ambient", YQ::Vec3f(0.05f, 0.05f, 0.05f));
	program->SetUniform("dirLight.diffuse", YQ::Vec3f(0.4f, 0.4f, 0.4f));
	program->SetUniform("dirLight.specular", YQ::Vec3f(0.5f, 0.5f, 0.5f));
	// point light 1
	program->SetUniform("pointLights[0].position", pointLightPositions[0]);
	program->SetUniform("pointLights[0].ambient", YQ::Vec3f(0.05f, 0.05f, 0.05f));
	program->SetUniform("pointLights[0].diffuse", YQ::Vec3f(0.8f, 0.8f, 0.8f));
	program->SetUniform("pointLights[0].specular", YQ::Vec3f(1.0f, 1.0f, 1.0f));
	program->SetUniform("pointLights[0].constant", 1.0f);
	program->SetUniform("pointLights[0].linear", 0.09f);
	program->SetUniform("pointLights[0].quadratic", 0.032f);
	// point light 2
	program->SetUniform("pointLights[1].position", pointLightPositions[1]);
	program->SetUniform("pointLights[1].ambient", YQ::Vec3f(0.05f, 0.05f, 0.05f));
	program->SetUniform("pointLights[1].diffuse", YQ::Vec3f(0.8f, 0.8f, 0.8f));
	program->SetUniform("pointLights[1].specular", YQ::Vec3f(1.0f, 1.0f, 1.0f));
	program->SetUniform("pointLights[1].constant", 1.0f);
	program->SetUniform("pointLights[1].linear", 0.09f);
	program->SetUniform("pointLights[1].quadratic", 0.032f);
	// point light 3
	program->SetUniform("pointLights[2].position", pointLightPositions[2]);
	program->SetUniform("pointLights[2].ambient", YQ::Vec3f(0.05f, 0.05f, 0.05f));
	program->SetUniform("pointLights[2].diffuse", YQ::Vec3f(0.8f, 0.8f, 0.8f));
	program->SetUniform("pointLights[2].specular", YQ::Vec3f(1.0f, 1.0f, 1.0f));
	program->SetUniform("pointLights[2].constant", 1.0f);
	program->SetUniform("pointLights[2].linear", 0.09f);
	program->SetUniform("pointLights[2].quadratic", 0.032f);
	// point light 4
	program->SetUniform("pointLights[3].position", pointLightPositions[3]);
	program->SetUniform("pointLights[3].ambient", YQ::Vec3f(0.05f, 0.05f, 0.05f));
	program->SetUniform("pointLights[3].diffuse", YQ::Vec3f(0.8f, 0.8f, 0.8f));
	program->SetUniform("pointLights[3].specular", YQ::Vec3f(1.0f, 1.0f, 1.0f));
	program->SetUniform("pointLights[3].constant", 1.0f);
	program->SetUniform("pointLights[3].linear", 0.09f);
	program->SetUniform("pointLights[3].quadratic", 0.032f);
	// spotLight
	program->SetUniform("spotLight.ambient", YQ::Vec3f(0.0f, 0.0f, 0.0f));
	program->SetUniform("spotLight.diffuse", YQ::Vec3f(1.0f, 1.0f, 1.0f));
	program->SetUniform("spotLight.specular", YQ::Vec3f(1.0f, 1.0f, 1.0f));
	program->SetUniform("spotLight.constant", 1.0f);
	program->SetUniform("spotLight.linear", 0.09f);
	program->SetUniform("spotLight.quadratic", 0.032f);
	program->SetUniform("spotLight.cutOff", cos(YQ::Math::DegreesToRadians(12.5f)));
	program->SetUniform("spotLight.outerCutOff", cos(YQ::Math::DegreesToRadians(15.0f)));

	std::function<void()> fun = [&]() {
		interactionPro.updateDelta();

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//绘制物体
		program->Use();
	
		YQ::Matrix4f view = camera.GetViweMatrix();
		program->SetUniform("view", view.Transposition());

		YQ::Matrix4f projection = YQ::Math::CreaPerspective(YQ::Math::DegreesToRadians(camera.GetScale()),
			wnd->Width() / (float)wnd->Height(), 0.1f, 100.0f);
		program->SetUniform("projection", projection.Transposition());

		program->SetUniform("viewPos", camera.GetCurPos());
		textur.Build();
		textur2.Build();

		program->SetUniform("spotLight.position", camera.GetCurPos());
		program->SetUniform("spotLight.direction", camera.GetFront());

		VAO.bindVertexArray();

		for (int i = 0; i < 10; ++i)
		{
			YQ::Matrix4f model = YQ::Matrix4f::CreateOnce();
			YQ::Math::Translate(model, cubePositions[i]);
			program->SetUniform("model", model.Transposition());

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		//绘制灯光
		lightProgram->Use();
		lightProgram->SetUniform("view", view.Transposition());
		lightProgram->SetUniform("projection", projection.Transposition());
		VAO_light.bindVertexArray();

		for (int i = 0; i < 4; ++i)
		{
			YQ::Matrix4f model = YQ::Matrix4f::CreateOnce();
			YQ::Math::Translate(model, pointLightPositions[i]);
			YQ::Math::Scale(model, YQ::Vec3f(0.2f, 0.2f, 0.2f));
			lightProgram->SetUniform("model", model.Transposition());

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
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
