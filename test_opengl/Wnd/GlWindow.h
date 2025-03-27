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
	void SetPrint(std::function<void()>fun);	//设置绘制函数
	void SetKeyEnter(std::function<void(int, int, int, int)> fun);	//设置键盘输入事件
	void SetMouseMove(std::function<void(double, double)> fun);
	void SetWheel(std::function<void(double, double)> fun);
	void SetInputMode(int mode, int value);
	
	int Height();
	int Width();
	void Close();

protected:
	friend class Application;
	GLFWwindow* m_pWnd;
	std::function<void()> m_funPrint = nullptr;
	std::function<void(int, int, int, int)> m_funKeyEnter = nullptr;
	std::function<void(double, double)> m_funMoudeMove = nullptr;
	std::function<void(double, double)> m_funWheel = nullptr;
	
	virtual void OnWndSizeChange(int nWidth, int nHeight);			//窗口改变大小
	virtual void OnProcessInput(int key, int scancode, int action, int mods);	//键盘输入
	virtual void OnPrint();			//绘制函数
	virtual void OnWndClose();		//窗口关闭函数
	virtual void OnMouseMove(double xpos, double ypos);
	virtual void OnWheel(double xpos, double ypos);

private:
	static std::map<GLFWwindow*, GlWindow*> m_mapping;

	static void OnWndSizeChange_g(GLFWwindow* wnd, int nWidth, int nHeight);
	static void OnProcessInput_g(GLFWwindow* wnd, int key, int scancode, int action, int mods);
	static void OnWndClose_g(GLFWwindow* wnd);
	static void OnMouseMove_g(GLFWwindow* wnd, double xpos, double ypos);
	static void OnWheel_g(GLFWwindow* wnd, double xpos, double ypos);
};
