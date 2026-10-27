/* 2154146 吴金轩 计科1班 */

#pragma once

#include <iostream>
#include <iomanip>
using namespace std;

/* 如果有其它全局函数需要声明，写于此处 */
int leap_year_determing(int year);
bool check_date(int y, int m, int d);

/* 如果有需要的宏定义、只读全局变量等，写于此处 */
const int month_days[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

/* Date类 */
class Date {
protected:
	int year;
	int month;
	int day;
public:
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
	friend Date operator+(Date& d, const int days);
	friend Date operator+(const int days, Date& d);
	friend Date operator-(const Date& d, const int days);
	friend int operator-(const Date& d1, const Date& d2);
	friend bool operator<(const Date& d1, const Date& d2);
	friend bool operator<=(const Date& d1, const Date& d2);
	friend bool operator>(const Date& d1, const Date& d2);
	friend bool operator>=(const Date& d1, const Date& d2);
	friend bool operator==(const Date& d1, const Date& d2);
	friend bool operator!=(const Date& d1, const Date& d2);
};
