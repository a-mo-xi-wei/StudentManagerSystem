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

	//�������������
	void popInputBox();
	void setInputBoxTitle(const string& title);
	void setText(const string& text);
	string text();
	void clear();
	void setCursorHide(bool isHide);//���ع��
	//�ı��Ƿ�ı�
	bool textChanged();

private:
	string m_pretext;	//��һ�ε�����
	string m_text;		//�б༭���е�����
	int textw;			//���ֿ��

	string m_title;	//�б༭������������
	bool m_hideCursor = false;		//�Ƿ���ʾ���
	bool m_isPopUp;	//�Ƿ񵯳�
};

