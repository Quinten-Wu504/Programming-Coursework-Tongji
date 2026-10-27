/* 2154146 吴金轩 计科 */
#pragma once
#include <iostream>
#include <string>
using namespace std;

#include "..\include\class_aat.h"
#include "..\include\class_crt.h"

class dbcfg {
protected:
	/* 文件目录 */
	string srcrootdir;

	/* 日志目录 */
	string logfile;
	int logsize = 0;

	/* 数据库信息 */
	string dbserver;
	int dbport;
	string dbuser;
	string dbpasswd;
	string dbname;
	string dbcurrterm;

	/* 读取配置信息的标志变量 */
	bool mark;
public:
	dbcfg(string cfgfile);

	string get_srcrootdir();
	string get_logfile();
	int get_logsize();
	string get_server();
	int get_port();
	string get_user();
	string get_passwd();
	string get_name();
	string get_currterm();

	bool is_set();

	void display();
};

