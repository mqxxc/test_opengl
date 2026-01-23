#include "Test_LightMapping.h"
#include "Application.h"
#include "GlWindow.h"
#include "GlProgram.h"
#include "YQMath.h"
#include "Camera.h"
#include "TextureUnit.h"
#include "InteractionPro.h"
#include "StaticVertexBuffer.h"
#include "VertexArray.h"

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

	glEnable(GL_DEPTH_TEST);		//开启深度测试

	Camera camera;
	camera.SetCameraPos({ 1.7f ,1.5f ,5.0f });
	camera.OnMoveView(0.0f, 120.0f);
	InteractionPro interactionPro;
	interactionPro.m_Camera = &camera;
	interactionPro.m_pWnd = wnd;

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
		textur.Build();
		textur2.Build();
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
