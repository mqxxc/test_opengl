#include "GlWindow.h"
#include "Application.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <iostream>

GlWindow::GlWindow(const std::string& strTitle, int nWidth, int nHeight)
{
	m_pWnd = glfwCreateWindow(nWidth, nHeight, strTitle.c_str(), NULL, NULL);

	if (m_pWnd == NULL)
	{
		std::cout << "create wnd error";
		return;
	}
	m_mapping[m_pWnd] = this;
	App->m_Wnds.push_back(this);

	glfwSetFramebufferSizeCallback(m_pWnd, GlWindow::OnWndSizeChange_g);
	glfwSetKeyCallback(m_pWnd, GlWindow::OnProcessInput_g);
	glfwSetWindowCloseCallback(m_pWnd, GlWindow::OnWndClose_g);
}

GlWindow::~GlWindow()
{
	App->OnWndClose(this);
	glfwDestroyWindow(m_pWnd);
}

void GlWindow::MakeContextCurrent()
{
	glfwMakeContextCurrent(m_pWnd);
	App->InitOPenGL();
}

void GlWindow::SetPrint(std::function<void()> fun)
{
	m_funPrint = fun;
}

int GlWindow::Height()
{
	int width, height;
	glfwGetWindowSize(m_pWnd, &width, &height);
	return height;
}

int GlWindow::Width()
{
	int width, height;
	glfwGetWindowSize(m_pWnd, &width, &height);
	return width;
}

void GlWindow::OnWndSizeChange(int nWidth, int nHeight)
{
	glViewport(0, 0, nWidth, nHeight);
}

void GlWindow::OnProcessInput(int key, int scancode, int action, int mods)
{
}

void GlWindow::OnPrint()
{
	glfwSwapBuffers(m_pWnd);
	m_funPrint();
}

void GlWindow::OnWndClose()
{
	App->OnWndClose(this);
}

void GlWindow::OnWndSizeChange_g(GLFWwindow* wnd, int nWidth, int nHeight)
{
	if (m_mapping.find(wnd) != m_mapping.end())
	{
		m_mapping[wnd]->OnWndSizeChange(nWidth, nHeight);
	}
}

void GlWindow::OnProcessInput_g(GLFWwindow* wnd, int key, int scancode, int action, int mods)
{
	if (m_mapping.find(wnd) != m_mapping.end())
	{
		m_mapping[wnd]->OnProcessInput(key, scancode, action, mods);
	}
}

void GlWindow::OnWndClose_g(GLFWwindow* wnd)
{
	if (m_mapping.find(wnd) != m_mapping.end())
	{
		m_mapping[wnd]->OnWndClose();
	}
}

std::map<GLFWwindow*, GlWindow*> GlWindow::m_mapping;