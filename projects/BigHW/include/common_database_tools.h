/* 2154146 Îâ½ðÐù ¼Æ¿Æ */
#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include "../include_mariadb_x86/mysql/mysql.h" 
using namespace std;

bool init_database(MYSQL*& mysql, const string& host, const string& user, const string& passwd, const string& name, const int& port);
int get_database_result(MYSQL*& mysql, MYSQL_RES*& result, const string& command);