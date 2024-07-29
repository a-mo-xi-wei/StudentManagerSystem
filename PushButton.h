#pragma once
#include "BasicWidget.h"
#include"Configure.h"
#include"Window.h"
class PushButton :
    public BasicWidget
{

public:
	PushButton(int x = 0, int y = 0, int w = 100, int h = 30);
	PushButton(const string& text, int x = 0, int y = 0, int w = 100, int h = 30);
	void show() override;
	void setText(const string& text);
	bool isIn();//�ж�����Ƿ��ڵ�ǰ��ť��
	bool IsClicked();//�ж�����Ƿ����˰�ť
	void eventLoop(const ExMessage& msg);
	void setBackgroundColor(COLORREF c);
	void setHoverColor(COLORREF c);
private:
	string m_btntext;
	ExMessage m_msg;

	COLORREF cur_c = RGB(126, 235, 215);//��ǰ��ɫ
	COLORREF normal_c = RGB(126, 235, 215);//������ɫ
	COLORREF hover_c = RGB(247, 255, 23);//����ƶ���ȥ����ɫ
};

