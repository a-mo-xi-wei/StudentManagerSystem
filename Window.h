#pragma once
#include"Configure.h"
class Window
{
public:
	Window(int w, int h, int flag);
	void setWindowTitle(const string& title);
	int exec();
	static int width();
	static int height();
	static void clear();
	static void beginDraw();
	static void flushDraw();
	static void endDraw();

	//����������������
	//�ж���û����Ϣ
	inline static bool hasMsg() { return ::peekmessage(&m_msg, EX_KEY | EX_MOUSE); }
	inline static const ExMessage& getMsg() { return m_msg; }

private:
	HWND m_handle;//���ھ��
	static ExMessage m_msg;//��Ϣ(��̬��Ա��ֻ��������δ����)
};

