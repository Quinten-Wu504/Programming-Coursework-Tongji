/* 2154146 Îâ½ðÐù ¼Æ¿Æ */
#pragma once
#include <iostream>
#include <string>
using namespace std;

class stuinfo {
protected:
	string stuno;
	string stuname;
public:
	stuinfo();
	stuinfo(const string& no, const string& name);
	void set(const string& no, const string& name);

	string get_stuno();
	string get_stuname();

	bool check_stuno();
	void append_stuno(const char s);
	void append_stuname(const char s);
};