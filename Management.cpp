#include "Management.h"
Management::Management()
{
	readFile("./text.txt");
	::loadimage(&m_bk, "./bk.jpg", Window::width(), Window::height());
	::settextstyle(27, 0, "楷体");
	//主界面按钮初始化
	menu_btns.push_back(new PushButton("查看学生"));
	menu_btns.push_back(new PushButton("添加学生"));
	menu_btns.push_back(new PushButton("删除学生"));
	menu_btns.push_back(new PushButton("修改学生"));
	menu_btns.push_back(new PushButton("查找学生"));
	menu_btns.push_back(new PushButton("退出系统"));
	for (int i = 0; i < menu_btns.size(); i++)
	{
		menu_btns[i]->setFixedSize(250, 50);
		int vspace = (Window::height() - menu_btns.size() * menu_btns[i]->height()) / 2 - 20;
		int bx = (Window::width() - menu_btns[i]->width()) / 2;
		int by = vspace + i * menu_btns[i]->height();
		menu_btns[i]->move(bx, by);
	}
	//初始化查看学生的表格
	m_insertTable.setRowCount(16);
	m_insertTable.setHeader(m_header);
	for (auto& val : vec_stu)
	{
		m_insertTable.insertData(val.formatInfo());
	}
	m_insertTable.move((Window::width() - m_insertTable.width()) / 2, 50);
	//添加页面
	m_insertEdit.setFixedSize(600, 30);
	m_insertEdit.move((Window::width() - m_insertEdit.width()) / 2, (Window::height() - m_insertEdit.height()) / 2);
	m_insertBtn.setFixedSize(60, 40);
	m_insertBtn.move(m_insertEdit.x() + m_insertEdit.width() + 20, m_insertEdit.y());
	m_insertBtn.setText("确定");
	//删除页面
	delEdit = new LineEdit(0, 0, 200, 30);
	delBtn = new PushButton("删除", 0, 0, 200, 30);
	delTable = new Table;
	delTable->setRowCount(6);
	delTable->setHeader(m_header);
	delEdit->setInputBoxTitle("请输入学生学号");
	delEdit->move((Window::width() - (delEdit->width() * 2 + 20)) / 2, Window::height() / 3);
	delBtn->move(delEdit->x() + delEdit->width() + 20, Window::height() / 3);
	delTable->move((Window::width() - delTable->width()) / 2, Window::height() / 3 + 100);
	//修改页面
	m_modifyEdit = new LineEdit(0, 0, 200, 30);
	m_modifyEdit->move((Window::width() - m_modifyEdit->width()) / 2, Window::height() / 3);
	int width = 120;	//修改页表格宽度
	int w = width * 6;
	int vspace = (Window::width() - w) / 2;
	for (int i = 0; i < 6; i++)
	{
		m_stuEdits.push_back(new LineEdit(vspace + i * width, m_modifyEdit->y() + 120, width, 30));
		m_stuEdits[i]->setCursorHide(true);	//隐藏光标
	}
	m_stuEdits[0]->setInputBoxTitle("请输入学号");
	m_stuEdits[1]->setInputBoxTitle("请输入姓名");
	m_stuEdits[2]->setInputBoxTitle("请输入班级");
	m_stuEdits[3]->setInputBoxTitle("请输入数学成绩");
	m_stuEdits[4]->setInputBoxTitle("请输入语文成绩");
	m_stuEdits[5]->setInputBoxTitle("请输入英语成绩");
	//查找页面
	searchEdit = new LineEdit(0, 0, 200, 30);
	searchIdBtn = new PushButton("按学号查找", 0, 0, 200, 30);
	searchNameBtn = new PushButton("按姓名查找", 0, 0, 200, 30);
	searchTable = new Table;
	searchTable->setRowCount(6);
	searchTable->setHeader(m_header);
	searchIdBtn->move((Window::width() - searchIdBtn->width()) / 2, Window::height() / 4);
	searchNameBtn->move((Window::width() - searchNameBtn->width()) / 2, Window::height() / 4 + searchNameBtn->height());
	searchEdit->move((Window::width() - searchEdit->width()) / 2, Window::height() / 3);
	searchTable->move((Window::width() - searchTable->width()) / 2, Window::height() / 3 + 100);
}

void Management::run()
{
	//获取菜单的返回值
	opt = Menu;
	Window::beginDraw();
	while (true) {
		Window::clear();
		drawBackground();

		if (Window::hasMsg())
		{
			m_msg = Window::getMsg();
			switch (m_msg.message)
			{
			case WM_KEYDOWN://按键按下
				//按ESC退出操作，返回主界面
				if (m_msg.vkcode == VK_ESCAPE)
				{
					opt = Menu;
				}
				break;
			default://鼠标操作
				this->eventLoop();
				break;
			}
		}

		switch (opt)
		{
		case Management::Menu:
			opt = menu();
			break;
		case Management::Display:
			display();
			break;
		case Management::Insert:
			add();
			break;
		case Management::Remove:
			erase();
			break;
		case Management::Modify:
			modify();
			break;
		case Management::Search:
			search();
			break;
		default:
			writeFile("./text.txt");
			exit(666);
			break;
		}
		Window::flushDraw();
	}
	Window::endDraw();

}

int Management::menu()
{
	string title = "欢迎进入学生成绩管理系统";
	settextcolor(RGB(225, 68, 237));
	settextstyle(60, 0, "楷体");
	int tx = (Window::width() - textwidth(title.c_str())) / 2;
	outtextxy(tx, 30, title.c_str());

	for (int i = 0; i < menu_btns.size(); i++) {
		menu_btns[i]->show();
		menu_btns[i]->eventLoop(m_msg);
		if (menu_btns[i]->IsClicked())
		{
			return i;
		}
	}
	return Menu;
}

void Management::updateTableData()
{
	m_insertTable.clear();
	for (auto val : vec_stu)
	{
		m_insertTable.insertData(val.formatInfo());
	}
}

void Management::display()
{
	m_insertTable.show();
}

void Management::add()
{
	settextstyle(50, 0, "黑体");
	char title[50] = "添加学生";
	settextcolor(RED);
	outtextxy((Window::width() - textwidth(title)) / 2, 50, title);
	m_insertEdit.show();
	m_insertBtn.show();
	settextstyle(30, 0, "黑体");
	settextcolor(BLACK);
	outtextxy(m_insertEdit.x(), m_insertEdit.y() - 150, "请依次输入<学号 姓名 班级 数学 语文 英语>");
	//添加按钮按下
	if (m_insertBtn.IsClicked())
	{
		string newData = m_insertEdit.text();
		if (newData.empty() || std::count(newData.begin(), newData.end(), ' ') != 5)
		{
			return;
		}
		//格式化数据
		replace(newData.begin(), newData.end(), ' ', '\t');
		//把数据放入表格，下次show的时候多输出数据
		m_insertTable.insertData(newData);
		//让数据写入文件
		Student t;
		t.formatWrite(newData);
		vec_stu.push_back(t);
		m_insertEdit.clear();
		updateTableData();
	}
}

void Management::erase()
{
	settextstyle(50, 0, "黑体");
	settextcolor(RED);
	char title[50] = "删除学生";
	outtextxy((Window::width() - textwidth(title)) / 2, 50, title);
	delEdit->show();
	delBtn->show();
	delTable->show();
	static vector<Student>::iterator delIt = vec_stu.end();
	if (delEdit->textChanged())
	{
		string info = delEdit->text();
		if (info.empty())
			return;
		Student stu;
		stringstream stream(info);
		stream >> stu.number;
		delIt = find(vec_stu.begin(), vec_stu.end(), stu);
		if (delIt != vec_stu.end())
		{
			delTable->insertData(delIt->formatInfo());
		}
	}
	//删除按钮按下
	if (delBtn->IsClicked() && delIt != vec_stu.end())
	{
		vec_stu.erase(delIt);
		delTable->clear();
		delIt = vec_stu.end();
		updateTableData();
	}

}

void Management::modify()
{
	settextstyle(50, 0, "黑体");
	settextcolor(RED);
	char title[50] = "修改学生";
	outtextxy((Window::width() - textwidth(title)) / 2, 50, title);
	m_modifyEdit->show();
	for (int i = 0; i < 6; i++)
	{
		m_stuEdits[i]->show();
	}
	settextstyle(30, 0, "黑体");
	outtextxy(m_modifyEdit->x() - 80, m_modifyEdit->y() - 80, "请输入需要修改的学生学号");
	//settextstyle(18, 0, "黑体");
	//outtextxy(m_stuEdits[0]->x(), m_stuEdits[0]->y()-40, "点击对应格子即可修改");
	if (m_modifyEdit->textChanged())
	{
		string res = m_modifyEdit->text();
		Student stu;
		stringstream stream(res);
		stream >> stu.number;
		//stu.name = res;
		auto findIt = find(vec_stu.begin(), vec_stu.end(), stu);
		if (findIt != vec_stu.end())
		{
			m_modifyIt = findIt;
			haveStu = true;
			//searchTable->insert(findIt->formatInfo());
			m_stuEdits[0]->setText(to_string(findIt->number));
			m_stuEdits[1]->setText(findIt->name);
			m_stuEdits[2]->setText(findIt->grade);
			m_stuEdits[3]->setText(to_string(findIt->math));
			m_stuEdits[4]->setText(to_string(findIt->chinese));
			m_stuEdits[5]->setText(to_string(findIt->english));
			findIt->display();
		}
		else {
			haveStu = false;

		}
	}

	if (haveStu)
	{
		//如果修改了学生信息
		for (int i = 0; i < 6; i++)
		{
			if (m_stuEdits[i]->textChanged())
			{
				switch (i)
				{
				case 0:		//修改了学号
					m_modifyIt->number = atoi(m_stuEdits[i]->text().data());
					break;
				case 1:		//修改了姓名
					m_modifyIt->name = m_stuEdits[i]->text();
					break;
				case 2:		//修改了班级
					m_modifyIt->grade = m_stuEdits[i]->text();
					break;
				case 3:		//修改了数学
					m_modifyIt->math = atoi(m_stuEdits[i]->text().data());
					break;
				case 4:		//修改了语文
					m_modifyIt->chinese = atoi(m_stuEdits[i]->text().data());
					break;
				case 5:		//修改了英语
					m_modifyIt->english = atoi(m_stuEdits[i]->text().data());
					break;
				}
				updateTableData();
			}
		}
	}
	else if (!isfirst)
	{
		settextstyle(18, 0, "黑体");
		setfillcolor(RGB(194, 195, 201));
		solidrectangle(m_stuEdits[0]->x(), m_stuEdits[0]->y(), m_stuEdits[0]->x() + 6 * 120, m_stuEdits[0]->y() + 30);
		outtextxy(m_stuEdits[0]->x(), m_stuEdits[0]->y() + 5, "未找到你要修改的学生，请查证后重试~");
	}
	else
	{
		settextstyle(18, 0, "黑体");
		setfillcolor(RGB(194, 195, 201));
		solidrectangle(m_stuEdits[0]->x(), m_stuEdits[0]->y(), m_stuEdits[0]->x() + 6 * 120, m_stuEdits[0]->y() + 30);
		outtextxy(m_stuEdits[0]->x(), m_stuEdits[0]->y() + 5, "请在上方输入框中输入要查找的学生学号，然后点击此处信息直接编辑");
	}

}

void Management::search()
{
	settextstyle(50, 0, "黑体");
	settextcolor(RED);
	char title[50] = "查找学生";
	outtextxy((Window::width() - textwidth(title)) / 2, 50, title);
	int where = -1;		//记录时按学号查找还是按姓名查找
	//查找按钮按下
	if (searchIdBtn->IsClicked())
	{
		searchEdit->setInputBoxTitle("请输入学号");
		searchEdit->popInputBox();
		where = 0;
	}
	if (searchNameBtn->IsClicked())
	{
		searchEdit->setInputBoxTitle("请输入姓名");
		searchEdit->popInputBox();
		where = 1;
	}
	searchIdBtn->show();
	searchNameBtn->show();
	searchTable->show();
	string res = searchEdit->text();
	if (!res.empty())
	{
		Student stu;
		stringstream stream(res);

		if (where == 0)
		{
			stream >> stu.number;
			auto findIt = find(vec_stu.begin(), vec_stu.end(), stu);//学号不会重复
			if (!searchTable->dataEmpty())
			{
				searchTable->clear();
			}
			if (findIt != vec_stu.end())
			{
				searchTable->insertData(findIt->formatInfo());
				findIt->display();
			}
		}
		else if (where == 1)
		{
			stream >> stu.name;
			if (!searchTable->dataEmpty())
			{
				searchTable->clear();
			}
			for (Student& s : vec_stu)//名字可能会重复
			{
				if (s.name == stu.name)
				{
					searchTable->insertData(s.formatInfo());
					s.display();
				}
			}
		}
	}

}

void Management::drawBackground()
{
	::putimage(0, 0, &m_bk);
}

void Management::eventLoop()
{
	if (opt == Display)
		m_insertTable.eventLoop(m_msg);
	else if (opt == Insert)
	{
		m_insertBtn.eventLoop(m_msg);
		m_insertEdit.eventLoop(m_msg);
	}
	else if (opt == Remove)
	{
		delTable->eventLoop(m_msg);
		delBtn->eventLoop(m_msg);
		delEdit->eventLoop(m_msg);
	}
	else if (opt == Modify)
	{
		m_modifyEdit->eventLoop(m_msg);

		if (haveStu)
		{
			for (int i = 0; i < 6; i++)
			{
				m_stuEdits[i]->eventLoop(m_msg);
			}
		}
	}
	else if (opt == Search)
	{
		searchTable->eventLoop(m_msg);
		searchIdBtn->eventLoop(m_msg);
		searchNameBtn->eventLoop(m_msg);
		searchEdit->eventLoop(m_msg);
	}
}

void Management::readFile(const string& fileName)
{
	fstream read(fileName, ios::in);
	if (!read.is_open())
	{
		return;
	}
	//读取表头
	char buf[1024] = { 0 };
	read.getline(buf, 1024);
	m_header = buf;
	//读取数据
	while (!read.eof())
	{
		char data[1024] = { 0 };
		read.getline(data, 1024);
		//跳过空行
		if (strlen(data) == 0)
		{
			break;
		}
		//格式化读取
		Student stu;
		stringstream ss(data);
		ss >> stu.number >> stu.name >> stu.grade >> stu.math >> stu.chinese >> stu.english;
		vec_stu.push_back(stu);
		cout << stu.number << stu.name << stu.grade << stu.math << stu.chinese << stu.english << endl;
	}
	read.close();
}

void Management::writeFile(const string& fileName)
{
	fstream write(fileName, ios::out | ios::trunc);//覆盖再重写
	if (!write.is_open())
	{
		cerr << fileName << " file open faild" << endl;
		return;
	}
	//写表头
	m_header += "\n";
	write.write(m_header.c_str(), m_header.size());
	//写数据
	for (auto& val : vec_stu)
	{
		string info = val.formatInfo();
		write.write(info.c_str(), info.size());
	}
	write.close();
}