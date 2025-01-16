#pragma once
#include <string>
#include <map>
#include <functional>

struct GLFWwindow;
class GlWindow
{
public:
	GlWindow(const std::string& strTitle, int nWidth, int nHeight);
	virtual ~GlWindow();
	void MakeContextCurrent();			//绑定当前窗口为gl上下文
	void Exec(std::function<void()>fun);	//开启事件循环

	static void InitGLFWwindow(int nVersionMajor, int nVersionMinor);		//初始化opengl
	static void TerminateGLF();												//释放GLF

protected:
	GLFWwindow* m_pWnd;
	
	virtual void OnWindoSizeChange(int nWidth, int nHeight);			//窗口改变大小
	virtual void OnProcessInput(int key, int scancode, int action, int mods);	//键盘输入

private:
	static std::map<GLFWwindow*, GlWindow*> m_mapping;

	static void OnWindoSizeChange_g(GLFWwindow* wnd, int nWidth, int nHeight);
	static void OnProcessInput_g(GLFWwindow* wnd, int key, int scancode, int action, int mods);
};

