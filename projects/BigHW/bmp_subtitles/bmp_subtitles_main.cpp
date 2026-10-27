/* 2154146 吴金轩 计科 */
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "bmp_subtitles.h"
#include "../include/class_aat.h"
#include "../include/common_string_process.h"
using namespace std;

const string style_type[] = { "horizontal", "vertical", "" };

enum OPT_ARGS {
	ARGS_BMPFILE = 0,
	ARGS_OUTFILE,
	ARGS_TRADITIONAL,
	ARGS_SUBTITLES,
	ARGS_POSX,
	ARGS_POSY,
	ARGS_COLOR,
	ARGS_STYLE
};

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
static void usage(const char* const argv0)
{
	char procname[256];

	/* 从"xx\\xx\\txt_compare.exe形式的argv[0]中截取txt_compare出来" */
	intercept_file_path(procname, argv0);

	ostringstream msg;
	const int wkey = 7 + strlen(procname) + 1;
	const int wopt = 7 + strlen(procname) + 4;
	cout << endl;

	msg << procname << " [Ver1.0.0]" << endl;
	msg << endl;

	msg << "Usage: " << procname << " --bmpfile filename1.bmp [ --outfile filename2.bmp --traditional --subtitles str" << endl;
	msg << setw(wkey) << ' ' << "--posx 0..1919 --posy 0..1079 --color HHHHHH --style horizontal/vertical ]" << endl;

	msg << setw(wkey) << ' ' << "必选项：" << endl;
	msg << setw(wopt) << ' ' << "--bmpfile filename1.bmp        : 指定bmp输入文件" << endl;
	msg << endl;

	msg << setw(wkey) << ' ' << "可选项：" << endl;
	msg << setw(wopt) << ' ' << "--outfile filename2.bmp        : 指定bmp输出文件（无此项默认输出文件名字为 filename1-副本.bmp）" << endl;
	msg << setw(wopt) << ' ' << "--traditional                  : 指定字幕为简体/繁体" << endl;
	msg << setw(wopt) << ' ' << "--subtitles str                : 指定字幕（无此项即无字幕）" << endl;
	msg << setw(wopt) << ' ' << "--posx x                       : 指定要加入的第一个汉字的左上角x坐标（无此项则x为0）" << endl;
	msg << setw(wopt) << ' ' << "\t取值[0..1919]" << endl;
	msg << setw(wopt) << ' ' << "--posy y                       : 指定要加入的第一个汉字的左上角y坐标（无此项则x为0）" << endl;
	msg << setw(wopt) << ' ' << "\t取值[0..1079]" << endl;
	msg << setw(wopt) << ' ' << "--color HHHHHH                 : 指定汉字前景色，6个16进制字符，分别为RGB（无此项则前景色为纯黑色）" << endl;
	msg << setw(wopt) << ' ' << "--style horizontal/vertical    : 指定字幕显示风格，横向/纵向（无此项则默认为horizontal）" << endl;
	msg << setw(wopt) << ' ' << "\thorizontal   : 横向显示" << endl;
	msg << setw(wopt) << ' ' << "\tvertical     : 纵向显示" << endl;

	cout << msg.str() << endl;
}


/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int main(int argc, char** argv)
{
	int need_fixed_args = 0;

	args_analyse_tools args[] = {
		args_analyse_tools("--bmpfile",			ST_EXTARGS_TYPE::str,					1, string("")),
		args_analyse_tools("--outfile",			ST_EXTARGS_TYPE::str,					1, string("")),
		args_analyse_tools("--traditional",		ST_EXTARGS_TYPE::boolean,				0, false),
		args_analyse_tools("--subtitles",		ST_EXTARGS_TYPE::str,					1, string("")),
		args_analyse_tools("--posx",			ST_EXTARGS_TYPE::int_with_default,		1, 0, 0, 1919),
		args_analyse_tools("--posy",			ST_EXTARGS_TYPE::int_with_default,		1, 0, 0, 1079),
		args_analyse_tools("--color",			ST_EXTARGS_TYPE::str,					1, string("000000")),
		args_analyse_tools("--style",			ST_EXTARGS_TYPE::str_with_set_default,	1, 0, style_type),
		args_analyse_tools()
	};

	if ((args_analyse_process(argc, argv, args, need_fixed_args)) < 0 || !args[ARGS_BMPFILE].existed()) {
		usage(argv[0]);
		return -1;
	}
	else {
		ifstream infile;
		fstream outfile;
		string infile_name = args[ARGS_BMPFILE].get_string();
		string outfile_name = args[ARGS_OUTFILE].get_string();
		string captions = args[ARGS_SUBTITLES].get_string();
		string color = args[ARGS_COLOR].get_string();
		string style = args[ARGS_STYLE].get_string();
		bool traditional = args[ARGS_TRADITIONAL].existed();
		int beg_x = args[ARGS_POSX].get_int();
		int beg_y = args[ARGS_POSY].get_int();
		
		bitmap_image image(infile_name);
		set_outfilename(image, outfile_name);
		infile.open(infile_name, ios::in | ios::binary);
		if (infile.is_open() == 0)
		{
			cout << "打开文件失败！" << endl;
			return -1;
		}
		outfile.open(outfile_name, ios::out | ios::in | ios::binary | ios::trunc);
		if (infile.is_open() == 0)
		{
			cout << "打开文件失败！" << endl;
			infile.close();
			return -1;
		}


		copy_bmpfile(infile, outfile, outfile_name);
		print_captions(image, captions, outfile, traditional, beg_x, beg_y, color, style);


		infile.close();
		outfile.close();
		return 0;
	}

}