#pragma once
#include "Test_CoordinateSystem.h"
#include "GlWindow.h"
#include "GlProgram.h"
#include "TextureUnit.h"
#include "Application.h"
#include "YQMath.h"
#include "StaticVertexBuffer.h"
#include "VertexArray.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <iostream>

void Test::CoordinateSystem()
{
	Application app;
	GlWindow* wnd = new GlWindow("LearnOpenGL", 800, 600);
	wnd->MakeContextCurrent();

	GlProgram* program = new GlProgram;
	program->CreateVertexShaderFromFile("resources/shader/CoordinateSystem.vs");
	program->CreateFragmentShaderFromFile("resources/shader/CoordinateSystem.fs");
	program->Complete();

	float vertices[] = {
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

	StaticVertexBuffer VBO;
	VBO.CreateVBO(5);
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
	layoutList[1].attributeLength = 2;

	VertexArray VAO;
	VAO.setupVBO(layoutList);
	VAO.bindVertexArray();

	TextureUnit texture1(GL_TEXTURE0);
	texture1.SetRowAround(TextureUnit::eREPEAT);
	texture1.SetColumnAround(TextureUnit::eREPEAT);
	texture1.SetAmplifyStrategy(TextureUnit::eNEAREST);
	texture1.SetShrinkStrategy(TextureUnit::eNEAREST);
	texture1.LoadImg("resources/img/container.jpg");
	texture1.CreateGenerateMipmap();

	TextureUnit texture2(GL_TEXTURE1);
	texture2.SetRowAround(TextureUnit::eREPEAT);
	texture2.SetColumnAround(TextureUnit::eREPEAT);
	texture2.SetAmplifyStrategy(TextureUnit::eNEAREST);
	texture2.SetShrinkStrategy(TextureUnit::eNEAREST);
	texture2.LoadImg("resources/img/awesomeface.png", true);
	texture2.CreateGenerateMipmap();

	program->Use();

	program->SetTextureUnit(&texture1, "Texture1");
	program->SetTextureUnit(&texture2, "Texture2");

	YQ::Matrix4f model; 
	YQ::Matrix4f view = YQ::Matrix4f::CreateOnce();
	YQ::Matrix4f projection;

	YQ::Math::Translate(view, YQ::Vec3f(0.0f, 0.0f, -3.0f));

	projection = YQ::Math::CreaPerspective(YQ::Math::DegreesToRadians(45.0f), 
		wnd->Width() / (float)wnd->Height(), 0.1f, 100.0f);

	glEnable(GL_DEPTH_TEST);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	std::function<void()> fun = [&]() {
		//传入模型矩阵
		model = YQ::Math::Rotate(YQ::Matrix4f::CreateOnce(), 
			(float)glfwGetTime() * YQ::Math::DegreesToRadians(50.0f), YQ::Vec3f(0.5f, 1.0f, 0.0f));

		program->SetUniform("model", model.Transposition());

		//传入观察矩阵
		program->SetUniform("view", view.Transposition());

		//传入投影矩阵
		program->SetUniform("projection", projection.Transposition());

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	};

	wnd->SetPrint(fun);
	app.Exec();

	delete program;
	delete wnd;
}
