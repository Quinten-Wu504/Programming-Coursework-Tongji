/* 2154146 吴金轩 计科1班 */
#include <iostream>
#include <iomanip>
#include "17-b2-datetime.h"
using namespace std;

/* --- 给出DateTime类的成员函数的体外实现(含友元及其它必要的公共函数)  ---

	几个重要提示：
	1、6参构造函数能否空函数体，直接激活Date和Time的构造函数？
	2、1参构造函数，能否不用循环，直接借助Date和Time的一参构造来快速实现？
	3、DateTime转long long的类型转换函数，能否不用循环，借助赋值兼容规则快速实现（(最短可以做到只有一句return)）
	4、DateTime土n的操作，需要定义几个类型的运算符重载？
*/

bool check_datetime(int y, int mo, int d, int h, int mi, int s)
{
	if (check_date(y, mo, d) && check_time(h, mi, s))
		return 1;
	else
		return 0;
}

DateTime::DateTime() :Date(), Time()
{
}

DateTime::DateTime(int y, int mo, int d, int h, int mi, int s)
{
	if (check_datetime(y, mo, d, h, mi, s))
	{
		year = y;
		month = mo;
		day = d;

		hour = h;
		minute = mi;
		second = s;
	}
	else
	{
		year = 1900;
		month = 1;
		day = 1;

		hour = 0;
		minute = 0;
		second = 0;
	}
}

DateTime::DateTime(long long int x) :Date((int)((x / (24 * 60 * 60) - (x < 0)) % (Date(2099, 12, 31) + 1))), Time((int)(x % (24 * 60 * 60)))
{
}

DateTime::DateTime(const DateTime& dt)
{
	year = dt.year;
	month = dt.month;
	day = dt.day;

	hour = dt.hour;
	minute = dt.minute;
	second = dt.second;
}

void DateTime::set(int y, int mo, int d, int h, int mi, int s)
{
	if (check_datetime(y, mo, d, h, mi, s))
	{
		year = y;
		month = mo;
		day = d;

		hour = h;
		minute = mi;
		second = s;
	}
	else
	{
		year = 1900;
		month = 1;
		day = 1;

		hour = 0;
		minute = 0;
		second = 0;
	}
}

void DateTime::get(int& y, int& mo, int& d, int& h, int& mi, int& s)
{
	y = year;
	mo = month;
	d = day;

	h = hour;
	mi = minute;
	s = second;
}

void DateTime::show()
{
	cout << *this << endl;
}

DateTime::operator long long int()
{
	return (long long int)((int)Date(year, month, day)) * 24 * 60 * 60 + (int)Time(hour, minute, second);
}

DateTime& DateTime::operator++()
{
	*this = (long long int)(*this) + 1;

	return *this;
}

DateTime DateTime::operator++(int)
{
	DateTime dt1(*this);

	*this = (long long int)(*this) + 1;

	return dt1;
}

DateTime& DateTime::operator--()
{
	*this = (long long int)(*this) - 1;

	return *this;
}

DateTime DateTime::operator--(int)
{
	DateTime dt1(*this);

	*this = (long long int)(*this) - 1;

	return dt1;
}

ostream& operator<<(ostream& out, const DateTime& dt)
{
	out << setfill('0');
	out << dt.year << "-" << setw(2) << dt.month << "-" << setw(2) << dt.day;
	out << " ";
	out << setw(2) << dt.hour << ":" << setw(2) << dt.minute << ":" << setw(2) << dt.second;
	out << setfill(' ');
	return out;
}

istream& operator>>(istream& in, DateTime& dt)
{
	int y1 = 0, mo1 = 0, d1 = 0, h1 = 0, mi1 = 0, s1 = 0;
	in >> y1 >> mo1 >> d1 >> h1 >> mi1 >> s1;
	dt.set(y1, mo1, d1, h1, mi1, s1);
	return in;
}

DateTime operator+(DateTime& dt, const long long int seconds)
{
	long long int sum = seconds + (long long int)dt;

	return DateTime(sum);
}

DateTime operator+(DateTime& dt, const int seconds)
{
	long long int sum = (long long int)dt + seconds;

	return DateTime(sum);
}

DateTime operator+(const long long int seconds, DateTime& dt)
{
	long long int sum = seconds + (long long int)dt;

	return DateTime(sum);
}

DateTime operator+(const int seconds, DateTime& dt)
{
	long long int sum = (long long int)dt + seconds;

	return DateTime(sum);
}

DateTime operator-(const DateTime& dt, const long long int seconds)
{
	DateTime temp(dt);

	temp = (long long int)temp - seconds;

	return temp;
}

DateTime operator-(const DateTime& dt, const int seconds)
{
	DateTime temp(dt);

	temp = (long long int)temp - seconds;

	return temp;
}

long long int operator-(const DateTime& dt1, const DateTime& dt2)
{
	DateTime temp1(dt1), temp2(dt2);

	return ((long long int)temp1 - (long long int)temp2);
}

bool operator<(const DateTime& dt1, const DateTime& dt2)
{
	Time temp1(dt1), temp2(dt2);
	return ((long long int)(temp1) < (long long int)(temp2));
}

bool operator<=(const DateTime& dt1, const DateTime& dt2)
{
	Time temp1(dt1), temp2(dt2);
	return ((long long int)(temp1) <= (long long int)(temp2));
}

bool operator>(const DateTime& dt1, const DateTime& dt2)
{
	Time temp1(dt1), temp2(dt2);
	return ((long long int)(temp1) > (long long int)(temp2));
}

bool operator>=(const DateTime& dt1, const DateTime& dt2)
{
	Time temp1(dt1), temp2(dt2);
	return ((long long int)(temp1) >= (long long int)(temp2));
}

bool operator==(const DateTime& dt1, const DateTime& dt2)
{
	Time temp1(dt1), temp2(dt2);
	return ((long long int)(temp1) == (long long int)(temp2));
}

bool operator!=(const DateTime& dt1, const DateTime& dt2)
{
	Time temp1(dt1), temp2(dt2);
	return ((long long int)(temp1) != (long long int)(temp2));
}


#if defined(__linux) || defined(__linux__)

DateTime operator+(DateTime& dt, const long int seconds)
{
	long long int sum = (long long int)dt + seconds;

	return DateTime(sum);
}

DateTime operator+(const long int seconds, DateTime& dt)
{
	long long int sum = (long long int)dt + seconds;

	return DateTime(sum);
}

DateTime operator-(const DateTime& dt, const long int seconds)
{
	DateTime temp(dt);

	temp = (long long int)temp - seconds;

	return temp;
}
#endif // __linux__