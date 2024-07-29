#include"Management.h"
#include"Window.h"
#include"Table.h"

int main()
{
	Window w(1080, 720, EX_NOMINIMIZE);
	w.setWindowTitle("学生成绩管理系统");
	Management m;
	m.run();
	system("pause");
	return 0;
}