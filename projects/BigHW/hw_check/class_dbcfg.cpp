/* 2154146 吴金轩 计科 */
#include "class_dbcfg.h"

dbcfg::dbcfg(string cfgfile)
{
	mark = 1;

	cfgfile_read_tools cfg(cfgfile);
	if (cfg.is_open() == 0)
	{
		cout << "配置文件 [" << cfgfile << "] 无法打开." << endl;
		mark = 0;
		return;
	}

	string gname = "[文件目录]";
	string iname = "src_rootdir";
	if (cfg.item_get_value(gname.c_str(), iname.c_str(), "", srcrootdir, 0) < 0)
	{
		cout << "取配置文件 [" << cfgfile << "] 的" << gname << "组的[" << iname << "]项的值出错." << endl;
		mark = 0;
		return;
	}

	gname = "[日志目录]";
	iname = "db_hw_logfile";
	if (cfg.item_get_value(gname.c_str(), iname.c_str(), "", logfile, 0) < 0)
	{
		cout << "取配置文件 [" << cfgfile << "] 的" << gname << "组的[" << iname << "]项的值出错." << endl;
		mark = 0;
		return;
	}

	iname = "db_hw_logsize";
	if (cfg.item_get_value(gname.c_str(), iname.c_str(), 0, INT_MAX, 1048576, logsize, 0) < 0)
	{
		cout << "取配置文件 [" << cfgfile << "] 的" << gname << "组的[" << iname << "]项的值出错." << endl;
		mark = 0;
		return;
	}

	gname = "[数据库]";
	iname = "db_host";
	if (cfg.item_get_value(gname.c_str(), iname.c_str(), "", dbserver, 0) < 0)
	{
		cout << "取配置文件 [" << cfgfile << "] 的" << gname << "组的[" << iname << "]项的值出错." << endl;
		mark = 0;
		return;
	}

	iname = "db_port";
	if (cfg.item_get_value(gname.c_str(), iname.c_str(), 0, 8888, 3306, dbport, 0) < 0)
	{
		cout << "取配置文件 [" << cfgfile << "] 的" << gname << "组的[" << iname << "]项的值出错." << endl;
		mark = 0;
		return;
	}

	iname = "db_name";
	if (cfg.item_get_value(gname.c_str(), iname.c_str(), "", dbname, 0) < 0)
	{
		cout << "取配置文件 [" << cfgfile << "] 的" << gname << "组的[" << iname << "]项的值出错." << endl;
		mark = 0;
		return;
	}

	iname = "db_username";
	if (cfg.item_get_value(gname.c_str(), iname.c_str(), "", dbuser, 0) < 0)
	{
		cout << "取配置文件 [" << cfgfile << "] 的" << gname << "组的[" << iname << "]项的值出错." << endl;
		mark = 0;
		return;
	}

	iname = "db_passwd";
	if (cfg.item_get_value(gname.c_str(), iname.c_str(), "", dbpasswd, 0) < 0)
	{
		cout << "取配置文件 [" << cfgfile << "] 的" << gname << "组的[" << iname << "]项的值出错." << endl;
		mark = 0;
		return;
	}

	iname = "db_currterm";
	if (cfg.item_get_value(gname.c_str(), iname.c_str(), "", dbcurrterm, 0) < 0)
	{
		cout << "取配置文件 [" << cfgfile << "] 的" << gname << "组的[" << iname << "]项的值出错." << endl;
		mark = 0;
		return;
	}
}

string dbcfg::get_srcrootdir()
{
	return srcrootdir;
}

string dbcfg::get_logfile()
{
	return logfile;
}

int dbcfg::get_logsize()
{
	return logsize;
}

string dbcfg::get_server()
{
	return dbserver;
}

int dbcfg::get_port()
{
	return dbport;
}

string dbcfg::get_user()
{
	return dbuser;
}

string dbcfg::get_passwd()
{
	return dbpasswd;
}

string dbcfg::get_name()
{
	return dbname;
}

string dbcfg::get_currterm()
{
	return dbcurrterm;
}

bool dbcfg::is_set()
{
	return mark;
}

void dbcfg::display()
{
	cout << "==============================================================================" << endl;
	cout << "当前配置信息如下：" << endl;
	cout << "==============================================================================" << endl;
	cout << "src_rootdir  =  " << srcrootdir << endl;
	cout << endl;
	cout << "logfile      =  " << logfile << endl;
	cout << "logsize      =  " << logsize << endl;
	cout << endl;
	cout << "db_host      =  " << dbserver << endl;
	cout << "db_name      =  " << dbname << endl;
	cout << "db_username  =  " << dbuser << endl;
	cout << "db_passwd    =  " << dbpasswd << endl;
	cout << "db_currterm  =  " << dbcurrterm << endl;
	cout << "==============================================================================" << endl;
}