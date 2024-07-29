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
	//启动管理类
	void run();

	int menu();
	void updateTableData();
	//1.显示所有学生
	void display();
	//2.添加学生
	void add();
	//3.删除
	void erase();
	//4.修改
	void modify();
	//5.查找
	void search();

	void drawBackground();
	void eventLoop();

	void readFile(const string& fileName);
	void writeFile(const string& fileName);
private:
	int opt;//选择
	IMAGE m_bk;
	ExMessage m_msg;
	vector<PushButton*>menu_btns;

private://读取文件，保存学生信息
	string m_header;
	vector<Student>vec_stu;

public://添加学生页（add）
	Table		m_insertTable;
	LineEdit	m_insertEdit;		//添加学生编辑框
	PushButton	m_insertBtn;		//添加学生确认按钮
public://删除学生页面
	LineEdit* delEdit;
	PushButton* delBtn;
	Table* delTable;
public://修改学生页
	LineEdit* m_modifyEdit;		//添加学生编辑框
	vector<LineEdit*> m_stuEdits;
	vector<Student>::iterator m_modifyIt; //指向要修改的学生
	bool haveStu = false;			//是否有要修改的学生
	bool isfirst = true;
public://查找学生页面
	LineEdit* searchEdit;
	PushButton* searchIdBtn;
	PushButton* searchNameBtn;
	Table* searchTable;
};

