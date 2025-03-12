#include "Test_CoordinateSystem.h"
#include "GlWindow.h"
#include "GlProgram.h"
#include "TextureUnit.h"
#include "Application.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <iostream>

void Test::CoordinateSystem()
{
	Application app;
	GlWindow* wnd = new GlWindow("LearnOpenGL", 800, 600);
	wnd->MakeContextCurrent();

	GlProgram* program = new GlProgram;
	program->CreateVertexShaderFromFile("src/shader/CoordinateSystem.vs");
	program->CreateFragmentShaderFromFile("src/shader/CoordinateSystem.fs");
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

	//顶点输入
	unsigned int VBO, VAO;

	//绑定顶点缓存
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);	//拷贝数据到顶点缓存中

	//顶点数组对象
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);//启用顶点属性
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);//启用顶点属性

	TextureUnit texture1(GL_TEXTURE0);
	texture1.SetRowAround(TextureUnit::eREPEAT);
	texture1.SetColumnAround(TextureUnit::eREPEAT);
	texture1.SetAmplifyStrategy(TextureUnit::eNEAREST);
	texture1.SetShrinkStrategy(TextureUnit::eNEAREST);
	texture1.LoadImg("src/img/container.jpg");
	texture1.CreateGenerateMipmap();

	TextureUnit texture2(GL_TEXTURE1);
	texture2.SetRowAround(TextureUnit::eREPEAT);
	texture2.SetColumnAround(TextureUnit::eREPEAT);
	texture2.SetAmplifyStrategy(TextureUnit::eNEAREST);
	texture2.SetShrinkStrategy(TextureUnit::eNEAREST);
	texture2.LoadImg("src/img/awesomeface.png", true);
	texture2.CreateGenerateMipmap();

	program->Use();

	program->SetTextureUnit(&texture1, "Texture1");
	program->SetTextureUnit(&texture2, "Texture2");

	glm::mat4 model = glm::mat4(1.0f);

	glm::mat4 view;
	view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));

	glm::mat4 projection;
	projection = glm::perspective(glm::radians(45.0f), wnd->Width() / (float)wnd->Height(), 0.1f, 100.0f);

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	std::function<void()> fun = [&]() {
		//传入模型矩阵
		model = glm::rotate(glm::mat4(1.0f), (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
		program->SetUniform("model", model);

		//传入观察矩阵
		program->SetUniform("view", view);

		//传入投影矩阵
		program->SetUniform("projection", projection);

		glClear(GL_COLOR_BUFFER_BIT);
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	};

	wnd->SetPrint(fun);
	app.Exec();

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	delete program;
	delete wnd;
}
