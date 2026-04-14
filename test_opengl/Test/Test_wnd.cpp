//你好,窗口
#pragma once
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Test_wnd.h"

#include <iostream>

void HelloWindow()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);	//指定大版本号为3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);	//指定小版本号为3
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);	//指定opengl模式

	//创建一个窗口
	GLFWwindow* window = glfwCreateWindow(800, 600, "Hello Window", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Create Window Failed " << std::endl;
		return;
	}
	glfwMakeContextCurrent(window);
	//初始化opengl
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return;
	}
	//绑定窗口回调函数
	glfwSetFramebufferSizeCallback(window, OnWindoSizeChange);

	while (!glfwWindowShouldClose(window))
	{
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
}

void OnWindoSizeChange(GLFWwindow* wnd, int nWidth, int nHeight)
{
	//设置渲染视口参数
	glViewport(0, 0, 800, 600);
}
