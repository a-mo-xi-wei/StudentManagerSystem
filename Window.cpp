#include "Window.h"

//C++17֮ǰ��Ҫ��cpp�ļ�����������һ�²���
ExMessage Window::m_msg;

Window::Window(int w, int h, int flag)
{
	m_handle = ::initgraph(w, h, flag);//::����˼��ȫ�ֺ���//����һ�����ھ��
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