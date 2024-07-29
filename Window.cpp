#include "Window.h"

//C++17之前需要在cpp文件中这样定义一下才行
ExMessage Window::m_msg;

Window::Window(int w, int h, int flag)
{
	m_handle = ::initgraph(w, h, flag);//::的意思是全局函数//返回一个窗口句柄
	::setbkmode(TRANSPARENT);
}

void Window::setWindowTitle(const string& title) {
	::SetWindowText(m_handle, title.c_str());
}

int Window::exec()
{
	return getchar();
}

int Window::width()
{
	return ::getwidth();
}

int Window::height()
{
	return ::getheight();
}

void Window::clear()
{
	::cleardevice();
}

void Window::beginDraw()
{
	::BeginBatchDraw();
}

void Window::flushDraw()
{
	::FlushBatchDraw();
}

void Window::endDraw()
{
	::EndBatchDraw();
}