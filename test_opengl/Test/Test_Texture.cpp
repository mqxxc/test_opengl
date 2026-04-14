#include "Test_Texture.h"
#include "GlWindow.h"
#include "GlProgram.h"
#include "TextureUnit.h"
#include "Application.h"
#include "../Gl/StaticVertexBuffer.h"
#include "../Gl/VertexArray.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <iostream>

void Test::Preliminary_Texture()
{
	Application app;
	GlWindow* wnd = new GlWindow("LearnOpenGL", 800, 600);
	wnd->MakeContextCurrent();

	GlProgram* program = new GlProgram;
	program->CreateVertexShaderFromFile("resources/shader/Preliminary_Texture.vs");
	program->CreateFragmentShaderFromFile("resources/shader/Preliminary_Texture.fs");
	program->Complete();

	float vertices[] = {
		//     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
			 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
			 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
			-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
			-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上
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

	VAO.bindVertexArray();
	//索引对象
	GLuint EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	int indices[] = {
		0, 1, 3,
		1, 2, 3
	};
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

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
	texture2.LoadImg("resources/img/awesomeface.png" , true);
	texture2.CreateGenerateMipmap();

	program->Use();
	program->SetTextureUnit(&texture1, "Texture1");
	program->SetTextureUnit(&texture2, "Texture2");

	int posSize = sizeof(indices) / sizeof(float);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	std::function<void()> fun = [&]() {
		glClear(GL_COLOR_BUFFER_BIT);
		glDrawElements(GL_TRIANGLES, posSize, GL_UNSIGNED_INT, 0);
	};

	wnd->SetPrint(fun);
	app.Exec();

	delete program;
	delete wnd;
}
