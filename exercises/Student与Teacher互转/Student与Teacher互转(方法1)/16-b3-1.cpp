/* 2154146 吴金轩 计科1班 */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
using namespace std;

/* 此处允许添加必须的定义或声明（不允许全局变量） */
class Teacher;
char* strncat_tj(char* s1, const char* s2, const unsigned int len)
{
	char if_NULL[80] = "";
	char* temp_s1 = s1;
	char* temp_s2 = (char*)s2;

	if (s2 == NULL) {
		s2 = if_NULL;
	}

	int length_cat = strlen(s2) > len ? len : strlen(s2);

	if (s1 != NULL) {
		s1 = s1 + strlen(s1);

		for (; s2 < temp_s2 + length_cat; s1++, s2++) {
			*s1 = *s2;
		}
		*s1 = '\0';
		s1 = temp_s1;
	}

	return s1;
}


char* strncpy_tj(char* s1, const char* s2, const unsigned int len)
{
	char if_NULL[80] = "";
	char* temp_s1 = s1;
	char* temp_s2 = (char*)s2;

	if (s2 == NULL) {
		s2 = if_NULL;
	}

	int length_cpy = strlen(s2) > len ? len : strlen(s2);

	if (s1 != NULL) {
		for (; s2 < temp_s2 + length_cpy; s1++, s2++) {
			*s1 = *s2;
		}
		s1 = temp_s1;
	}

	return s1;
}

/* Student 类的定义（成员函数不允许体内实现） */
class Student {
private:
	int num;	//学号
	char name[16];	//姓名
	char sex;	//性别，只能是 F/M 两种，大小写不敏感
	char addr[64];	//家庭住址
public:
	Student();
	Student(const int num1, const char* name1, const char sex1, const char* addr1);
	friend ostream& operator<<(ostream& out, const Student& stu);
	friend Teacher;
};

/* ----给出Student类成员函数及友元函数的体外实现---- */
Student::Student()
{
	//缺省值 - 学号：2150000 姓名：<学生S> 性别：M 地址：四平路1239号
	num = 2150000;
	strcpy(name, "<学生S>");
	sex = 'M';
	strcpy(addr, "四平路1239号");
}

Student::Student(const int num1, const char* name1, const char sex1, const char* addr1)
{
	num = num1;
	strcpy(name, name1);
	sex = sex1;
	strcpy(addr, addr1);
}

ostream& operator<<(ostream& out, const Student& stu)
{
	out << stu.num << " " << stu.name << " " << stu.sex << " " << stu.addr;
	return out;
}

/* Teacher 类的定义（成员函数不允许体内实现） */
class Teacher {
private:
	int num;	//工号
	char name[16];	//姓名
	char sex;	//性别，只能是 F/M 两种，大小写不敏感
	char addr[64];	//家庭住址
public:
	Teacher();
	Teacher(const int num1, const char* name1, const char sex1, const char* addr1);
	friend ostream& operator<<(ostream& out, const Teacher& te);
	Teacher(Student stu);
	operator Student();
	//公有部分允许添加成员函数（体外实现），不允许添加数据成员、友元声明
};

/* ----给出Teacher类成员函数及友元函数的体外实现---- */
Teacher::Teacher()
{
	//缺省值 - 工号：21000 姓名：<教师T> 性别：M 地址：四平路1239号衷和楼
	num = 21000;
	strcpy(name, "<教师T>");
	sex = 'M';
	strcpy(addr, "四平路1239号衷和楼");
}

Teacher::Teacher(const int num1, const char* name1, const char sex1, const char* addr1)
{
	num = num1;
	strcpy(name, name1);
	sex = sex1;
	strcpy(addr, addr1);
}

Teacher::Teacher(Student stu)
{
	/* 学生转教师测试：
		学号转工号规则：工号 = 21 + 学号后三位
		姓名转换规则：前两个汉字转换为"教师"，后续字符不变
		性别转换规则：原样转换
		地址转换规则：原地址后加"电信学院"(不考虑字符串越界)    */
	num = stu.num % 1000 + 21000;
	strcpy(name, stu.name);
	strncpy_tj(name, "教师", strlen("教师"));
	sex = stu.sex;
	strcpy(addr, stu.addr);
	strncat_tj(addr, "电信学院", strlen("电信学院"));
}

Teacher::operator Student()
{
	/* 教师转学生测试：
		工号转学号规则：学号 = 2150 + 工号后三位
		姓名转换规则：前两个汉字转换为"学生"，后续字符不变
		性别转换规则：原样转换
		地址转换规则：原地址后加"101室"(不考虑字符串越界)    */
	Student stu;
	
	stu.num = num % 1000 + 2150000;
	strcpy(stu.name, name);
	strncpy_tj(stu.name, "学生", strlen("学生"));
	stu.sex = sex;
	strcpy(stu.addr, addr);
	strncat_tj(stu.addr, "101室", strlen("101室"));

	return stu;
}

ostream& operator<<(ostream& out, const Teacher& te)
{
	out << te.num << " " << te.name << " " << te.sex << " " << te.addr;
	return out;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：main函数不准动
***************************************************************************/
int main()
{
	Student s1;	//缺省值 - 学号：2150000 姓名：<学生S> 性别：M 地址：四平路1239号
	Student s2 = Student(2151234, "学生甲", 'M', "曹安公路4800号");
	Teacher t1;	//缺省值 - 工号：21000 姓名：<教师T> 性别：M 地址：四平路1239号衷和楼
	Teacher t2 = Teacher(21123, "教师A", 'F', "曹安公路4800号智信馆");

	/* 打印原始学生信息 */
	cout << "学生信息：" << s1 << endl;				//期望输出："学生信息：2150000 <学生S> M 四平路1239号"
	cout << "学生信息：" << s2 << endl;				//期望输出："学生信息：2151234 学生甲 M 曹安公路4800号"
	cout << endl;

	/* 打印原始教师信息 */
	cout << "教师信息：" << t1 << endl;				//期望输出："教师信息：21000 <教师T> M 四平路1239号衷和楼"
	cout << "教师信息：" << t2 << endl;				//期望输出："教师信息：21123 教师A F 曹安公路4800号智信馆"
	cout << endl;

	/* 学生转教师测试：
		学号转工号规则：工号 = 21 + 学号后三位
		姓名转换规则：前两个汉字转换为"教师"，后续字符不变
		性别转换规则：原样转换
		地址转换规则：原地址后加"电信学院"(不考虑字符串越界)    */
	t1 = s2;
	cout << "学生信息：" << s2 << endl;				//期望输出："学生信息：2151234 学生甲 M 曹安公路4800号"
	cout << "转换为教师的信息：" << t1 << endl;		//期望输出："转换为教师的信息：21234 教师甲 M 曹安公路4800号电信学院"
	cout << endl;

	/* 教师转学生测试：
		工号转学号规则：学号 = 2150 + 工号后三位
		姓名转换规则：前两个汉字转换为"学生"，后续字符不变
		性别转换规则：原样转换
		地址转换规则：原地址后加"101室"(不考虑字符串越界)    */
	s1 = t2;
	cout << "教师信息：" << t2 << endl;				//期望输出："教师信息：21123 教师A F 曹安公路4800号智信馆"
	cout << "转换为学生的信息：" << s1 << endl;		//期望输出："转换为学生的信息：2150123 学生A F 曹安公路4800号智信馆101室"
	cout << endl;

	return 0;
}