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
	bool isIn();//判断鼠标是否在当前按钮上
	bool IsClicked();//判断鼠标是否点击了按钮
	void eventLoop(const ExMessage& msg);
	void setBackgroundColor(COLORREF c);
	void setHoverColor(COLORREF c);
private:
	string m_btntext;
	ExMessage m_msg;

	COLORREF cur_c = RGB(126, 235, 215);//当前颜色
	COLORREF normal_c = RGB(126, 235, 215);//正常颜色
	COLORREF hover_c = RGB(247, 255, 23);//鼠标移动上去的颜色
};

