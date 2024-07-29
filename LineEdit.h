#pragma once
#include "BasicWidget.h"
#include"Configure.h"
#include"Window.h"
class LineEdit :
	public BasicWidget
{
public:
	LineEdit(int x = 0, int y = 0, int w = 100, int h = 30);
	void show()override;
	void eventLoop(const ExMessage& msg);

	//弹出数据输入框
	void popInputBox();
	void setInputBoxTitle(const string& title);
	void setText(const string& text);
	string text();
	void clear();
	void setCursorHide(bool isHide);//隐藏光标
	//文本是否改变
	bool textChanged();

private:
	string m_pretext;	//上一次的文字
	string m_text;		//行编辑器中的文字
	int textw;			//文字宽度

	string m_title;	//行编辑器弹出窗标题
	bool m_hideCursor = false;		//是否显示光标
	bool m_isPopUp;	//是否弹出
};

