/* 2154146 吴金轩 计科1班 */
#include <iostream>
using namespace std;

/* 如果有其它全局函数需要声明，写于此处 */
int leap_year_determing(int year);

/* 如果有需要的宏定义、只读全局变量等，写于此处 */
const int month_days[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

/* 补全Date类的定义，所有成员函数均体外实现，不要在此处体内实现 */
class Date {
private:
	int year;
	int month;
	int day;
public:
	/* 根据需要定义所需的成员函数、友元函数等(不允许添加数据成员) */
	Date();
	Date(int y, int m, int d);
	Date(int x);
	Date(const Date& d);
	void set(int y, int m = 1, int d = 1);
	void get(int& y, int& m, int& d);
	void show();
	operator int();
	Date& operator++();
	Date operator++(int);
	Date& operator--();
	Date operator--(int);
	friend ostream& operator<<(ostream& out, const Date& d);
	friend istream& operator>>(istream& in, Date& d);
	friend Date operator+(const Date& d, const int days);
	friend Date operator+(const int days, const Date& d);
	friend Date operator-(const Date& d, const int days);
	friend int operator-(const Date& d1, const Date& d2);
	friend bool operator<(const Date& d1, const Date& d2);
};

