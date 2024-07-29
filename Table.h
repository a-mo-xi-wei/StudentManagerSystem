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
	//���ӵĿ�Ⱥ͸߶�
	int m_gridW;
	int m_gridH;
	//�������ֵĿ�Ⱥ͸߶�
	int m_tw;
	int m_th;
	string m_header;
	vector<string> m_datas;

private://��ҳ����
	int m_curPage;//��ǰҳ��
	int m_maxPage;//���ҳ��
	int m_extraData;//�����һҳû������ʣ������ݵĸ���
private://���Ӱ�ť
	PushButton* m_prevBtn;//��һҳ
	PushButton* m_nextBtn;//��һҳ
	PushButton* m_firstBtn;//��һҳ
	PushButton* m_lastBtn;//���һҳ
};

