#include "LineEdit.h"

LineEdit::LineEdit(int x, int y, int w, int h)
	:BasicWidget(x, y, w, h), textw(2), m_isPopUp(false), m_title("������") {}

void LineEdit::show()
{
	settextstyle(30, 0, "����");
	settextcolor(BLACK);
	setfillcolor(RGB(232, 232, 236));
	fillrectangle(m_x, m_y, m_x + m_w, m_y + m_h);
	if (!m_hideCursor)
	{
		//��˸��С����
		setlinecolor(RED);
		line(m_x + textw + 2, m_y + 2, m_x + textw + 2, m_y + m_h - 2);
	}
	//�����������edit��
	outtextxy(m_x, m_y + (m_h - textheight(m_text.c_str())) / 2, m_text.c_str());

	if (m_isPopUp)
	{
		m_pretext = m_text;
		popInputBox();
		m_isPopUp = false;
	}
}

void LineEdit::eventLoop(const ExMessage& msg)
{
	//�ж��Ƿ���Ҫ���������
	if (msg.x > m_x && msg.x < m_x + m_w && msg.y > m_y && msg.y < m_y + m_h
		&& msg.message == WM_LBUTTONDOWN)
	{
		m_isPopUp = true;
	}
}
void LineEdit::popInputBox()
{
	char str[1024] = { 0 };
	InputBox(str, 1024, nullptr, m_title.c_str(), m_text.c_str());
	m_text = str;
	textw = ::textwidth(m_text.c_str());
}
void LineEdit::setInputBoxTitle(const string& title)
{
	m_title = title;
}

void LineEdit::setText(const std::string& text)
{
	m_text = text;
	textw = ::textwidth(m_text.c_str());
}

std::string  LineEdit::text()
{
	return m_text;
}

void LineEdit::clear()
{
	m_text.clear();
	textw = 0;
}

void LineEdit::setCursorHide(bool isHide)
{
	m_hideCursor = isHide;
}

bool LineEdit::textChanged()
{
	if (m_pretext == m_text)
	{
		return false;
	}
	m_pretext = m_text;	//����,֪ͨһ���ı��ı伴��
	return true;
}