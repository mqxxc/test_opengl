#include "Test_Triangle.h"
#include "GlWindow.h"
#include "GlProgram.h"
#include "Application.h"
#include "../Gl/StaticVertexBuffer.h"
#include "../Gl/VertexArray.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <iostream>

void Test::Test_Triangle()
{
	Application app;
	GlWindow* wnd = new GlWindow("LearnOpenGL", 800, 600);
	wnd->MakeContextCurrent();

	GlProgram* program = new GlProgram;
	program->CreateVertexShaderFromFile("resources/shader/Triangle.vs");
	program->CreateFragmentShaderFromFile("resources/shader/Triangle.fs");
	program->Complete();

	float verArr[] = {
		//位置			  //颜色
		0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
		-0.5f,-0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
	    0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f
	};

	StaticVertexBuffer triangleVBO;
	triangleVBO.CreateVBO(6);
	triangleVBO.wirteData(verArr, sizeof(verArr) / sizeof(float));

	VertexArray triangleVAO;
	std::vector<VertexArray::VertexLayout> layoutList;
	layoutList.resize(2);
	
	layoutList[0].VBO = &triangleVBO;
	layoutList[0].dataTypeEnum = GL_FLOAT;
	layoutList[0].offset = 0;
	layoutList[0].unitLength = sizeof(float);
	layoutList[0].attributeLength = 3;

	layoutList[1].VBO = &triangleVBO;
	layoutList[1].dataTypeEnum = GL_FLOAT;
	layoutList[1].offset = 3;
	layoutList[1].unitLength = sizeof(float);
	layoutList[1].attributeLength = 3;
	triangleVAO.setupVBO(layoutList);

	triangleVAO.bindVertexArray();
	glUseProgram(program->ProgramID());

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	std::function<void()> fun = [&]() {
		glClear(GL_COLOR_BUFFER_BIT);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	};

	wnd->SetPrint(fun);
	app.Exec();
	
	delete program;
	delete wnd;
}