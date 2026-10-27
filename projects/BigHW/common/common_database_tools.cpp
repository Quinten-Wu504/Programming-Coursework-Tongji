/* 2154146 吴金轩 计科 */
#include "../include/common_database_tools.h"

bool init_database(MYSQL*& mysql, const string& host, const string& user, const string& passwd, const string& name, const int& port)
{
    /* 初始化 mysql 变量，失败返回NULL */
    if ((mysql = mysql_init(NULL)) == NULL)
    {
        cout << "mysql_init failed" << endl;
        return 0;
    }

    /* 连接数据库，失败返回NULL
       1、mysqld没运行
       2、没有指定名称的数据库存在 */
    if (mysql_real_connect(mysql, host.c_str(), user.c_str(), passwd.c_str(), name.c_str(), port, NULL, 0) == NULL)
    {
        cout << "mysql_real_connect failed(" << mysql_error(mysql) << ")" << endl;
        return 0;
    }

    /* 设置字符集，否则读出的字符乱码 */
    mysql_set_character_set(mysql, "gbk");
    return 1;
}

int get_database_result(MYSQL*& mysql, MYSQL_RES*& result, const string& command)
{
    /* 查询命令：
           select * from student
       含义：表示查询student表的所有记录，每条记录按原始顺序显示所有字段
       返回值：成功返回0，不成功非0
       不成功的常见可能性：
           1、查询字符串存在语法错误
           2、查询不存在的数据表 */
    if (mysql_query(mysql, command.c_str()))
    {
        cout << "mysql_query failed(" << mysql_error(mysql) << ")" << endl;
        return -1;
    }

    /* 将查询结果存储起来，出现错误则返回NULL
        注意：查询结果为NULL，不会返回NULL */
    if ((result = mysql_store_result(mysql)) == NULL)
    {
        cout << "mysql_store_result failed" << endl;
        return -1;
    }

    /* 当前查询到的记录的数量 */
    int num_rows = (int)mysql_num_rows(result);

    return num_rows;
}