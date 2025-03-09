#include "Application.h"
#include "GlWindow.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <assert.h>

Application::Application()
{
	assert(m_gPApp == nullptr && "Application repeat init");

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);	//指定大版本号
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);	//指定小版本号
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);	//指定opengl模式为核心模式

	m_gPApp = this;
}

Application::~Application()
{
	glfwTerminate();
}

Application* Application::getApp()
{
	return m_gPApp;
}

int Application::Exec()
{
	while (m_bRun)
	{
		glfwPollEvents();
		for (auto it : m_Wnds)
		{
			it->OnPrint();
		}
	}
	return 0;
}

void Application::Exit()
{
	m_bRun = false;
}

void Application::InitOPenGL()
{
	if (!m_bIniOpenglFun)
	{
		assert(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) && "gladLoadGLLoader error");
	}
}

void Application::OnWndClose(GlWindow* pWnd)
{
	m_Wnds.remove(pWnd);
	if (m_Wnds.empty())
	{
		Exit();
	}
}

Application* Application::m_gPApp;