#pragma once
#include"Window.h"
#include"PushButton.h"
#include"Student.h"
#include"Table.h"
#include"LineEdit.h"
#include"Configure.h"
class Management
{
	enum Operator
	{
		Display,
		Insert,
		Remove,
		Modify,
		Search,
		Menu = 66
	};

public:
	Management();
	//����������
	void run();

	int menu();
	void updateTableData();
	//1.��ʾ����ѧ��
	void display();
	//2.���ѧ��
	void add();
	//3.ɾ��
	void erase();
	//4.�޸�
	void modify();
	//5.����
	void search();

	void drawBackground();
	void eventLoop();

	void readFile(const string& fileName);
	void writeFile(const string& fileName);
private:
	int opt;//ѡ��
	IMAGE m_bk;
	ExMessage m_msg;
	vector<PushButton*>menu_btns;

private://��ȡ�ļ�������ѧ����Ϣ
	string m_header;
	vector<Student>vec_stu;

public://���ѧ��ҳ��add��
	Table		m_insertTable;
	LineEdit	m_insertEdit;		//���ѧ���༭��
	PushButton	m_insertBtn;		//���ѧ��ȷ�ϰ�ť
public://ɾ��ѧ��ҳ��
	LineEdit* delEdit;
	PushButton* delBtn;
	Table* delTable;
public://�޸�ѧ��ҳ
	LineEdit* m_modifyEdit;		//���ѧ���༭��
	vector<LineEdit*> m_stuEdits;
	vector<Student>::iterator m_modifyIt; //ָ��Ҫ�޸ĵ�ѧ��
	bool haveStu = false;			//�Ƿ���Ҫ�޸ĵ�ѧ��
	bool isfirst = true;
public://����ѧ��ҳ��
	LineEdit* searchEdit;
	PushButton* searchIdBtn;
	PushButton* searchNameBtn;
	Table* searchTable;
};

