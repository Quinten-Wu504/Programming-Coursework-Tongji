/* 2154146 吴金轩 计科1班 */

#pragma once

#include <iostream>
using namespace std;

/* 补全TString类的定义，所有成员函数均体外实现，不要在此处体内实现 */
class TString {
protected:
	char* content;
	int   len;
public:
	// 构造函数
	TString();
	TString(const int n, bool not_construct);
	TString(const char* s);
	TString(const TString& s_copy);

	// 析构函数
	~TString();

	// 取数据成员
	int length() const;
	const char* c_str() const;

	// set函数
	void set(const char* s);
	void set(const TString& s);


	// 计算相关重载函数
	friend TString operator+(const TString& s1, const char s2);
	friend TString operator+(const char s1, const TString& s2);
	friend TString operator+(const TString& s1, const char* s2);
	friend TString operator+(const char* s1, const TString& s2);
	friend TString operator+(const TString& s1, const TString& s2);

	friend TString operator-(const TString& s1, const char s2);
	friend TString operator-(const TString& s1, const char* s2);
	friend TString operator-(const TString& s1, const TString& s2);

	friend TString operator*(const TString& s, const int& n);

	TString& operator+=(const char s);
	TString& operator+=(const char* s);
	TString& operator+=(const TString& s);

	TString& operator-=(const char s2);
	TString& operator-=(const char* s2);
	TString& operator-=(const TString& s2);

	TString& operator*=(const int& n);

	TString& operator=(const TString& s);
	TString& operator=(const char* s);

	// []运算符重载
	char& operator[](const int n) const;

	// !运算符（反转字符串）的函数重载
	friend TString operator!(const TString& s);

	// 比较运算符重载
	friend bool operator<(const TString& s1, const TString& s2);
	friend bool operator<(const TString& s1, const char* s2);

	friend bool operator<=(const TString& s1, const TString& s2);
	friend bool operator<=(const TString& s1, const char* s2);

	friend bool operator>(const TString& s1, const TString& s2);
	friend bool operator>(const TString& s1, const char* s2);

	friend bool operator>=(const TString& s1, const TString& s2);
	friend bool operator>=(const TString& s1, const char* s2);

	friend bool operator==(const TString& s1, const TString& s2);
	friend bool operator==(const TString& s1, const char* s2);

	friend bool operator!=(const TString& s1, const TString& s2);
	friend bool operator!=(const TString& s1, const char* s2);

	// 流运算符重载
	friend ostream& operator<<(ostream& out, const TString& s);
	friend istream& operator>>(istream& in, TString& s);
};

int TStringLen(const TString& s);
