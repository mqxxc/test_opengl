#include "GlWindow.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <iostream>

GlWindow::GlWindow(const std::string& strTitle, int nWidth, int nHeight)
{
	m_pWnd = glfwCreateWindow(nWidth, nHeight, strTitle.c_str(), NULL, NULL);

	if (m_pWnd == NULL)
	{
		std::cout << "create wnd error";
	}
	m_mapping[m_pWnd] = this;

	glfwSetFramebufferSizeCallback(m_pWnd, GlWindow::OnWindoSizeChange_g);
	glfwSetKeyCallback(m_pWnd, GlWindow::OnProcessInput_g);
}

GlWindow::~GlWindow()
{
	glfwDestroyWindow(m_pWnd);
}

void GlWindow::MakeContextCurrent()
{
	glfwMakeContextCurrent(m_pWnd);
}

void GlWindow::Exec(std::function<void()> fun)
{
	while (!glfwWindowShouldClose(m_pWnd))
	{
		glfwSwapBuffers(m_pWnd);
		glfwPollEvents();

		fun();
	}
}

void GlWindow::InitGLFWwindow(int nVersionMajor, int nVersionMinor)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, nVersionMajor);	//指定大版本号
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, nVersionMinor);	//指定小版本号
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);	//指定opengl模式为核心模式
}

void GlWindow::TerminateGLF()
{
	glfwTerminate();
}

void GlWindow::OnWindoSizeChange(int nWidth, int nHeight)
{
	glViewport(0, 0, nWidth, nHeight);
}

void GlWindow::OnProcessInput(int key, int scancode, int action, int mods)
{
}

void GlWindow::OnWindoSizeChange_g(GLFWwindow* wnd, int nWidth, int nHeight)
{
	if (m_mapping.find(wnd) != m_mapping.end())
	{
		m_mapping[wnd]->OnWindoSizeChange(nWidth, nHeight);
	}
}

void GlWindow::OnProcessInput_g(GLFWwindow* wnd, int key, int scancode, int action, int mods)
{
	if (m_mapping.find(wnd) != m_mapping.end())
	{
		m_mapping[wnd]->OnProcessInput(key, scancode, action, mods);
	}
}



std::map<GLFWwindow*, GlWindow*> GlWindow::m_mapping;