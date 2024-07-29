#pragma once
#include"Configure.h"
using uint32 = unsigned int;

class Student
{
public:
	Student() {};
	Student(uint32 number, const string& name, const string& grade,
		uint32 math, uint32 chinese, uint32 english);
	void display();
	string formatInfo();//格式化数据
	void formatWrite(const string& str);
public:
	bool operator==(const Student& right) const;
	bool operator>(const Student& right) const;
	bool operator<(const Student& right) const;
public:
	//学号 姓名 班级 数学 语文 英语
	uint32 number;
	string name;
	string grade;
	uint32 math;
	uint32 chinese;
	uint32 english;
};

