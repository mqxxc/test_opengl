#pragma once
#include <list>
#define App Application::getApp()

class GlWindow;
class Application
{
public:
	Application();
	~Application();
	static Application* getApp();
	int Exec();
	void Exit();

private:
	static Application* m_gPApp;
	bool m_bIniOpenglFun = false;
	bool m_bRun = true;
	std::list<GlWindow*> m_Wnds;

	void InitOPenGL();
	void OnWndClose(GlWindow* pWnd);

	friend class GlWindow;
};
