#include "Student.h"

Student::Student(uint32 number, const string& name, const string& grade,
	uint32 math, uint32 chinese, uint32 english)
	:number(number), name(name), grade(grade), math(math), chinese(chinese), english(english) {}

void Student::display()
{
	cout << this->number << "\t" << this->name << "\t" << this->grade << "\t" << this->math << "\t" << this->chinese << "\t" << this->english << endl;
}

string Student::formatInfo()
{
	stringstream ss;
	ss << number << "\t" << name << "\t" << grade << "\t" << math << "\t" << chinese << "\t" << english << endl;
	return ss.str();
}

void Student::formatWrite(const string& str)
{
	stringstream ss(str);
	ss >> this->number >> this->name >> this->grade >> this->math >> this->chinese >> this->english;
}

bool Student::operator==(const Student& right) const
{
	return this->number == right.number;
}

bool Student::operator>(const Student& right) const
{
	return this->number > right.number;
}

bool Student::operator<(const Student& right) const
{
	return this->number < right.number;
}