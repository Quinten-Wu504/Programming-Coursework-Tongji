/* 2154146 Îâ½ðÐù ¼Æ¿Æ */
#pragma once
#include <iostream>
#include <string>
#include "class_stuinfo.h"
#include "..\include\common_string_process.h"
using namespace std;

class cross_check_list :public stuinfo {
protected:
	int number;
	stuinfo* list;
public:
	cross_check_list();
	cross_check_list(const string& hostno, const string& hostname, const string& comment_text);
	~cross_check_list();
	void set(const string& hostno, const string& hostname);
	void set(const string& hostno, const string& hostname, const string& comment_text);
	string check();
	void print_cross_check_list(cross_check_list*& cross_list, int stu_num);

	friend int find_stuno(cross_check_list*& cross_list, string stuno, int stu_num);
};