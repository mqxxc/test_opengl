#pragma once
#include <string>
#include <map>
#include <functional>

class Application;
struct GLFWwindow;
class GlWindow
{
public:
	GlWindow(const std::string& strTitle, int nWidth, int nHeight);
	virtual ~GlWindow();
	void MakeContextCurrent();			//绑定当前窗口为gl上下文
	void SetPrint(std::function<void()>fun);	//开启事件循环
	int Height();
	int Width();

protected:
	friend class Application;
	GLFWwindow* m_pWnd;
	std::function<void()> m_funPrint;
	
	virtual void OnWndSizeChange(int nWidth, int nHeight);			//窗口改变大小
	virtual void OnProcessInput(int key, int scancode, int action, int mods);	//键盘输入
	virtual void OnPrint();			//绘制函数
	virtual void OnWndClose();		//窗口关闭函数

private:
	static std::map<GLFWwindow*, GlWindow*> m_mapping;

	static void OnWndSizeChange_g(GLFWwindow* wnd, int nWidth, int nHeight);
	static void OnProcessInput_g(GLFWwindow* wnd, int key, int scancode, int action, int mods);
	static void OnWndClose_g(GLFWwindow* wnd);
};
