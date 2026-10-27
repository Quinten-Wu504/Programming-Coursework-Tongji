/* 2154146 Îâ½ğĞù ¼Æ¿Æ */
#include "class_stuinfo.h"

stuinfo::stuinfo()
{
	stuno = "";
	stuname = "";
}

stuinfo::stuinfo(const string& no, const string& name)
{
	stuno = no;
	stuname = stuname;
}

void stuinfo::set(const string& no, const string& name)
{
	stuno = no;
	stuname = stuname;
}

string stuinfo::get_stuno()
{
	return stuno;
}

string stuinfo::get_stuname()
{
	return stuname;
}

bool stuinfo::check_stuno()
{
	if (stuno.length() == 7)
		return 1;
	else
		return 0;
}

void stuinfo::append_stuno(const char s)
{
	stuno += s;
}

void stuinfo::append_stuname(const char s)
{
	stuname += s;
}