#pragma once
#include "BasicWidget.h"
#include"Configure.h"
#include"PushButton.h"
class Table :
	public BasicWidget
{
public:

	Table(int row = 0, int col = 0);
	~Table();
	void setRowCount(int row);
	void setColCount(int col);
	void setHeader(const string& header);
	void insertData(const string& data);
	bool dataEmpty();
	void clear();
	void show() override;
	void drawTableGrid();
	void drawButton();
	void drawTableData();
	void drawHeader();
	static vector<string>split(string str, char separator = '\t');
	void updatePage();
	void eventLoop(const ExMessage& msg);
private:

	int m_rows;
	int m_cols;
	//格子的宽度和高度
	int m_gridW;
	int m_gridH;
	//设置文字的宽度和高度
	int m_tw;
	int m_th;
	string m_header;
	vector<string> m_datas;

private://分页处理
	int m_curPage;//当前页数
	int m_maxPage;//最大页数
	int m_extraData;//若最后一页没满，则剩余的数据的个数
private://增加按钮
	PushButton* m_prevBtn;//上一页
	PushButton* m_nextBtn;//下一页
	PushButton* m_firstBtn;//第一页
	PushButton* m_lastBtn;//最后一页
};

