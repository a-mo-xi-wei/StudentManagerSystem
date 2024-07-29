#include "Table.h"

Table::Table(int row, int col)
	:BasicWidget(0, 0, 0, 0), m_rows(row), m_cols(col), m_curPage(1), m_maxPage(1), m_extraData(0)
{
	m_prevBtn = new PushButton("上一页");
	m_nextBtn = new PushButton("下一页");
	m_firstBtn = new PushButton("第一页");
	m_lastBtn = new PushButton("结尾页");
}

Table::~Table()
{
	delete m_prevBtn;
	delete m_nextBtn;
	delete m_firstBtn;
	delete m_lastBtn;
}

void Table::setRowCount(int row)
{
	m_rows = row;
}

void Table::setColCount(int col)
{
	m_cols = col;
}

void Table::setHeader(const string& header)
{
	m_header = header;
	//cout << "header " << m_header << endl;
	m_cols = count(m_header.begin(), m_header.end(), '\t') + 1;
	//cout << m_cols << endl;
	//求出文字的宽度和高度
	m_tw = ::textwidth("计算机1401");
	m_th = ::textheight(m_header.c_str());
	m_gridW = m_tw + 10;
	m_gridH = m_th + 10;
	m_w = m_cols * m_gridW;//整个表格的宽度
	m_h = m_rows * m_gridH;//整个表格的高度
}

void Table::insertData(const string& data)
{
	updatePage();
	m_datas.push_back(data);
}
bool Table::dataEmpty()
{
	if (m_datas.empty())
		return true;
	else
		return false;
}
void Table::clear()
{
	m_datas.clear();
	updatePage();
}

void Table::show()
{
	drawTableGrid();
	drawHeader();
	drawTableData();
}

void Table::drawTableGrid()
{
	//确定表格有多少行，多少列
	setlinecolor(YELLOW);

	//画横线
	for (int i = 0; i < m_rows + 1; i++)
	{
		line(m_x, m_y + i * m_gridH, m_x + m_cols * m_gridW, m_y + i * m_gridH);
	}

	//画竖线
	for (int i = 0; i < m_cols + 1; i++)
	{
		line(m_x + i * m_gridW, m_y, m_x + i * m_gridW, m_y + m_rows * m_gridH);
	}
	//绘制页数按钮
	drawButton();
}

void Table::drawButton()
{
	static bool flag = false;
	if (!flag)
	{
		//若是不做任何处理则会导致每次循环都要重复设置位置，但它的位置是固定的，因此进行以上处理
		m_prevBtn->move(m_x, m_y + m_h + 20);
		m_nextBtn->move(m_prevBtn->x() + m_prevBtn->width(), m_prevBtn->y());
		m_firstBtn->move(m_nextBtn->x() + m_nextBtn->width(), m_nextBtn->y());
		m_lastBtn->move(m_firstBtn->x() + m_firstBtn->width(), m_firstBtn->y());
		flag = true;
	}

	m_prevBtn->show();
	m_nextBtn->show();
	m_firstBtn->show();
	m_lastBtn->show();

	char str[30] = { 0 };
	sprintf_s(str, "第%d页/共%d页", m_curPage, m_maxPage);
	outtextxy(m_lastBtn->x() + m_lastBtn->width() + 100, m_lastBtn->y(), str);
}

void Table::drawHeader()
{
	setlinestyle(PS_SOLID, 2);
	::rectangle(m_x, m_y - m_gridH, m_x + m_w, m_y);
	for (int i = 0; i < m_cols; i++)
	{
		line(m_x + i * m_gridW, m_y - m_gridH, m_x + i * m_gridW, m_y);
	}
	//分割表头数据
	auto headers = split(m_header);
	settextcolor(RED);

	for (int i = 0; i < headers.size(); i++)
	{
		int tx = m_x + i * m_gridW + (m_gridW - textwidth(headers[i].c_str())) / 2;
		int ty = m_y - m_gridH + (m_gridH - textheight(headers[i].c_str())) / 2;
		outtextxy(tx, ty, headers[i].c_str());
	}

	setlinestyle(PS_SOLID, 1);
}

void Table::drawTableData()
{
	int begPos = (m_curPage - 1) * m_rows;
	int endPos = (m_curPage - 1) * m_rows + m_rows;

	if (m_curPage == m_maxPage)//防止越界
	{
		endPos = (m_curPage - 1) * m_rows + m_extraData + 1;
	}
	if (m_datas.empty())
		return;
	for (int i = begPos; i < endPos; i++)//行
	{
		const auto& line_data = split(m_datas[i]);
		for (int k = 0; k < line_data.size(); k++)//列
		{
			int tx = m_x + k * m_gridW + (m_gridW - ::textwidth(line_data[k].c_str())) / 2;
			int ty = m_y + (i % m_rows) * m_gridH + 5;
			settextcolor(BLACK);
			settextstyle(m_th, 0, "宋体");
			outtextxy(tx, ty, line_data[k].c_str());
		}
	}
}

vector<string> Table::split(string str, char separator)
{
	vector<string>res;
	for (int pos = 0; pos != string::npos;)
	{
		//查找指定分割字符的位置
		pos = str.find(separator);
		//取出字符串
		res.push_back(str.substr(0, pos));
		//把剩下的字符串保存到 str
		str = string(str.c_str() + pos + 1);
	}
	return res;
}

void Table::updatePage()
{
	if (m_datas.size() % m_rows == 0)
	{
		m_maxPage = (m_datas.size() / m_rows) + 1;
		m_extraData = m_datas.size() % m_rows;
	}
	else
	{
		m_maxPage = (m_datas.size() / m_rows) + 1;
		m_extraData = m_datas.size() % m_rows;
	}
}

void Table::eventLoop(const ExMessage& msg)
{
	m_prevBtn->eventLoop(msg);
	m_nextBtn->eventLoop(msg);
	m_firstBtn->eventLoop(msg);
	m_lastBtn->eventLoop(msg);
	if (m_prevBtn->IsClicked())
	{
		if (m_curPage != 1)
		{
			m_curPage--;
		}
	}
	if (m_nextBtn->IsClicked())
	{
		if (m_curPage != m_maxPage)
		{
			m_curPage++;
		}
	}
	if (m_firstBtn->IsClicked())
	{
		m_curPage = 1;
	}
	if (m_lastBtn->IsClicked())
	{
		m_curPage = m_maxPage;
	}
}