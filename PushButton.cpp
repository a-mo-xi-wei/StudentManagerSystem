#include "PushButton.h"

PushButton::PushButton(int x, int y, int w, int h)
	:BasicWidget(x, y, w, h) {}

PushButton::PushButton(const string& text, int x, int y, int w, int h)
	:BasicWidget(x, y, w, h), m_btntext(text) {}


void PushButton::show()
{
	settextcolor(RGB(115, 75, 235));
	setfillcolor(cur_c);
	settextstyle(30, 0, "楷体");
	setlinecolor(WHITE);
	::fillroundrect(m_x, m_y, m_x + m_w, m_y + m_h, 10, 10);
	//把文字居中显示在按钮中间
	int tx = m_x + (m_w - textwidth(m_btntext.c_str())) / 2;
	int ty = m_y + (m_h - textheight(m_btntext.c_str())) / 2;
	::outtextxy(tx, ty, m_btntext.c_str());
}
void PushButton::setText(const string& text)
{
	this->m_btntext = text;
}
bool PushButton::isIn()
{
	if (m_msg.x >= m_x && m_msg.x <= m_x + m_w && m_msg.y >= m_y && m_msg.y <= m_y + m_h)
	{
		return true;
	}
	return false;
}

bool PushButton::IsClicked()
{
	if (isIn())
	{
		if (m_msg.message == WM_LBUTTONDOWN)
		{
			return true;
		}
	}
	return false;
}

void PushButton::eventLoop(const ExMessage& msg)
{
	m_msg = msg;
	//如果鼠标在按钮上
	if (isIn())
	{
		cur_c = hover_c;
		setlinestyle(PS_SOLID, 5);
		::fillroundrect(m_x, m_y, m_x + m_w, m_y + m_h, 10, 10);
		settextstyle(36, 0, "楷体");
		int tx = m_x + (m_w - textwidth(m_btntext.c_str())) / 2;
		int ty = m_y + (m_h - textheight(m_btntext.c_str())) / 2;
		::outtextxy(tx, ty, m_btntext.c_str());
		setlinestyle(PS_SOLID, 1);
		settextstyle(30, 0, "楷体");
	}
	else
	{
		cur_c = normal_c;
	}
}

void PushButton::setBackgroundColor(COLORREF c)
{
	normal_c = c;
}

void PushButton::setHoverColor(COLORREF c)
{
	hover_c = c;
}
