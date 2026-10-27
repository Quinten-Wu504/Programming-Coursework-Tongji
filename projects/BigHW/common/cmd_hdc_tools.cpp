/* 2154146 吴金轩 计科 */

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>
#include "../include/cmd_hdc_tools.h"
using namespace std;

#if !HDC_SERIES_BY_TEACHER	//未定义的情况下才打开条件编译

/* 允许添加需要的头文件 */
#include <math.h>

extern "C" WINBASEAPI HWND WINAPI GetConsoleWindow(); //VS中此处会有波浪线，不影响正常使用

/* 已定义的静态全局变量 */
static HWND hWnd = GetConsoleWindow();
static HDC hdc = NULL;
static const double PI = 3.14159;
static int _BgColor_, _FgColor_, _Width_, _High;
static int _Delay_ms;

/* 允许适度使用静态全局变量，但仅限static，即外部不可见 */

/* 此处允许添加自定义函数，但仅限static，即外部不可见 */

/* 下面给出了几个基本函数的完整实现，不要改动 */
/***************************************************************************
  函数名称：
  功    能：初始化
  输入参数：const int bgcolor：背景色
			const int fgcolor：前景色
			const int width  ：屏幕宽度（点阵）
			const int high   ：屏幕高度（点阵）
  返 回 值：
  说    明：
***************************************************************************/
void hdc_init(const int bgcolor, const int fgcolor, const int width, const int high)
{
	/* 先释放，防止不release而再次init（hdc_release可重入） */
	hdc_release();

	/* 窗口init后，用一个静态全局量记录，后续hdc_cls()会用到 */
	_BgColor_ = bgcolor;
	_FgColor_ = fgcolor;
	_Width_ = width;
	_High = high;

	hdc = GetDC(hWnd);

	cct_setcursor(CURSOR_INVISIBLE);
	cct_setcolor(bgcolor, fgcolor);
	cct_setfontsize("点阵字体", 16);
	cct_setconsoleborder(width / 8 + !!(width % 8), high / 16 + !!(high % 16)); //将点阵的宽度及高度转换为特定字体的行列数，!!的含义：如果不是8/16的倍数，行列多+1
	cct_cls();
}

/***************************************************************************
  函数名称：
  功    能：释放画图资源
  输入参数：
  返 回 值：
  说    明：可重入
***************************************************************************/
void hdc_release()
{
	if (hdc) {
		ReleaseDC(hWnd, hdc);
		hdc = NULL;
		cct_setcursor(CURSOR_VISIBLE_NORMAL);
	}
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void hdc_set_delay(int ms)
{
	if (ms > 0)
		_Delay_ms = ms;
	else
		_Delay_ms = 0;
}

/***************************************************************************
  函数名称：
  功    能：设置画笔颜色，传入RGB值
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void hdc_set_pencolor(const int RGB_value)
{
	SelectObject(hdc, GetStockObject(DC_PEN));
	SetDCPenColor(hdc, RGB_value);
}

/***************************************************************************
  函数名称：
  功    能：设置画笔颜色，传入RGB三色，值0-255
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void hdc_set_pencolor(const unsigned char red, const unsigned char green, const unsigned char blue)
{
	hdc_set_pencolor(RGB(red, green, blue));
}

/***************************************************************************
  函数名称：
  功    能：清除屏幕上现有的图形
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void hdc_cls()
{
	/* 发现一定要换一种颜色初始化才能清除像素点，找到更简便方法的同学可以通知我 */
	hdc_init(_BgColor_, (_FgColor_ + 1) % 16, _Width_, _High);

	hdc_init(_BgColor_, _FgColor_, _Width_, _High);

	/* 部分机器上运行demo时，会出现hdc_cls()后第一根线有缺线的情况，加延时即可
	   如果部分机器运行还有问题，调高此延时值 */
	Sleep(30);
}

/***************************************************************************
  函数名称：
  功    能：在(x,y)位置处用指定颜色画出一个像素点
  输入参数：const int x：x坐标，左上角为(0,0)
			const int y：y坐标，左上角为(0,0)
  返 回 值：
  说    明：颜色直接用当前设定，可以在调用处指定
***************************************************************************/
static inline void hdc_base_point(const int x, const int y)
{
	MoveToEx(hdc, x - 1, y - 1, NULL);
	LineTo(hdc, x, y);
	if (_Delay_ms > 0)
		Sleep(_Delay_ms);
}

/***************************************************************************
  函数名称：
  功    能：在(x1,y1)-(x2,y2)之间画出一个像素点的连线
  输入参数：const int x1：起点x坐标，左上角为(0,0)
			const int y1：起点y坐标，左上角为(0,0)
			const int x2：终点y坐标，左上角为(0,0)
			const int y2：终点y坐标，左上角为(0,0)
  返 回 值：
  说    明：颜色直接用当前设定
***************************************************************************/
static inline void hdc_base_line(const int x1, const int y1, const int x2, const int y2)
{
	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x2, y2);
	if (_Delay_ms > 0)
		Sleep(_Delay_ms);
}

/***************************************************************************
  函数名称：
  功    能：在(x,y)位置处用指定颜色画一个指定粗细的点(用画实心圆来模拟)
  输入参数：const int x			：x坐标，左上角为(0,0)
			const int y			：y坐标，左上角为(0,0)
			const int thickness	：点的粗细，下限位1，上限不限(如过大会导致不完全填充)（有缺省值）
			const int RGB_value	：点的颜色（有缺省值）
  返 回 值：
  说    明：改进运行效率
***************************************************************************/
void hdc_point(const int x, const int y, const int thickness, const int RGB_value)
{
	int tn = thickness;
	if (tn < 1)
		tn = 1;		//处理下限
	/* 不卡点直径的上限，但是单上限超过一定大小是，画出的圆部分位置未实心 */

	const int tn_end = (tn <= 1) ? 1 : tn / 2;

	int angle, level;
	int old_x1 = INT_MAX, old_y1 = INT_MAX, x1, y1;
	int count = 0;

	if (RGB_value != INVALID_RGB)
		hdc_set_pencolor(RGB_value);

	/* 用画圆的方式模拟粗点 */
	for (level = 1; level <= tn_end; level++) {
		for (angle = 0; angle <= 360; angle++) {
			/* 注意，系统的坐标轴，0°在圆的最下方 */
			x1 = x + (int)(level * sin(angle * PI / 180));
			y1 = y - (int)(level * cos(angle * PI / 180));

			/* 当半径很小时，角度变化不会引起int型的x1/y1变化，因此加判断语句，避免重复画同一像素点 */
			if (x1 != old_x1 || y1 != old_y1) {
				old_x1 = x1;
				old_y1 = y1;
				hdc_base_point(x1, y1);
				++count;
			}
		}
	}
#if 0
	/* 放开此注释，可以看到一个粗点用了几个像素点组成 */
	cct_gotoxy(0, 41);
	printf("count=%d           ", count);
	getchar();
#endif
}

/* -------------------------------------------------------------------------
	给出下列函数的实现，函数名及参数表不准改动
	1、不需要调用系统的其他有关图形操作的函数
	2、下列函数的实现都基于hdc_base_point/hdc_base_line函数的组合
	3、想一想，是不是所有函数都需要给出独立的实现过程？应该先实现哪些函数？
	4、填充是实现中最复杂的部分
	5、系统的角度与函数参数中的角度含义相差180°
   ------------------------------------------------------------------------- */

   /***************************************************************************
	 函数名称：
	 功    能：画线段
	 输入参数：const int x1		：起点的x
			   const int y1		：起点的y
			   const int x2		：终点的x
			   const int y2		：终点的y
			   const int thickness	：线段的粗细（有缺省值）
			   const int RGB_value	：线段的颜色（有缺省值）
	 返 回 值：
	 说    明：本函数可以用基于hdc_point的组合（速度慢）
					 也可以用hdc_base_point/hdc_base_line的组合（速度快）
   ***************************************************************************/
void hdc_line(const int x1, const int y1, const int x2, const int y2, const int thickness, const int RGB_value)
{
	int tn = thickness;
	if (tn < 1)
		tn = 1;

	int half_thickness = tn / 2;

	if (RGB_value != INVALID_RGB)
		hdc_set_pencolor(RGB_value);

	for (int level = half_thickness, i = 0; i < thickness; level--, i++) {
		hdc_base_line(x1 + level, y1, x2 + level, y2);
		hdc_base_line(x1, y1 + level, x2, y2 + level);
	}
}

/***************************************************************************
  函数名称：
  功    能：给出三点的坐标，画一个三角形
  输入参数：const int x1		：第1个点的x
			const int y1		：第1个点的y
			const int x2		：第2个点的x
			const int y2		：第2个点的y
			const int x3		：第3个点的x
			const int y3		：第3个点的y
			bool filled			：是否需要填充（有缺省值）
			const int thickness	：边的粗细（有缺省值）
			const int RGB_value	：颜色（有缺省值）
  返 回 值：
  说    明：不判断三点是否共线，如果共线，划出一条直线即可
***************************************************************************/
void hdc_triangle(const int x1, const int y1, const int x2, const int y2, const int x3, const int y3, bool filled, const int thickness, const int RGB_value)
{
	int temp_x1 = 0, temp_y1 = INT_MAX, temp_x2 = 0, temp_y2 = 0, temp_x3 = 0, temp_y3 = 0, tn = thickness;
	
	if (tn < 1)
		tn = 1;

	if (y1 == y2 && y2 == y3) {
		hdc_line(x1, y1, x2, y2, tn, RGB_value);
		hdc_line(x1, y1, x3, y3, tn, RGB_value);
	}
	else {
		temp_y1 = (y1 < y2) ? ((y1 < y3) ? y1 : y3) : ((y2 < y3) ? y2 : y3);
		temp_x1 = (y1 < y2) ? ((y1 < y3) ? x1 : x3) : ((y2 < y3) ? x2 : x3);
		temp_y3 = (y1 > y2) ? ((y1 > y3) ? y1 : y3) : ((y2 > y3) ? y2 : y3);
		temp_x3 = (y1 > y2) ? ((y1 > y3) ? x1 : x3) : ((y2 > y3) ? x2 : x3);
		temp_y2 = y1 + y2 + y3 - temp_y1 - temp_y3;
		temp_x2 = x1 + x2 + x3 - temp_x1 - temp_x3;

		hdc_line(temp_x1, temp_y1, temp_x2, temp_y2, tn, RGB_value);
		hdc_line(temp_x1, temp_y1, temp_x3, temp_y3, tn, RGB_value);
		hdc_line(temp_x2, temp_y2, temp_x3, temp_y3, tn, RGB_value);

		double angle_1_2 = 0;
		double angle_1_3 = 0;

		if (temp_y2 == temp_y1) {
			if (temp_x2 >= temp_x1)
				angle_1_2 = 0;
			else if (temp_x2 < temp_x1)
				angle_1_2 = PI;
		}
		else if (temp_x2 == temp_x1)
			angle_1_2 = PI / 2;
		else
			angle_1_2 = atan(float(temp_y1 - temp_y2) / float(temp_x1 - temp_x2));

		if (temp_y3 == temp_y1) {
			if (temp_x3 >= temp_x1)
				angle_1_3 = 0;
			else if (temp_x3 < temp_x1)
				angle_1_3 = PI;
		}
		else if (temp_x3 == temp_x1)
			angle_1_3 = PI / 2;
		else
			angle_1_3 = atan(float(temp_y1 - temp_y3) / float(temp_x1 - temp_x3));

		int new_temp_x2 = INT_MAX, new_temp_x3 = INT_MAX, new_temp_y2 = INT_MAX, new_temp_y3 = INT_MAX;
		int old_temp_x2 = INT_MAX, old_temp_x3 = INT_MAX, old_temp_y2 = INT_MAX, old_temp_y3 = INT_MAX;

		if (angle_1_2 < 0)
			angle_1_2 += PI;
		if (angle_1_3 < 0)
			angle_1_3 += PI;

		if (filled) {
			for (int i = 1; old_temp_x2 != temp_x2 || old_temp_y2 != temp_y2 || old_temp_x3 != temp_x3 || old_temp_y3 != temp_y3; i++) {
				if (old_temp_x2 != temp_x2)
					new_temp_x2 = temp_x1 + int(i * cos(angle_1_2));
				else
					new_temp_x2 = old_temp_x2;
				if (old_temp_y2 != temp_y2)
					new_temp_y2 = temp_y1 + int(i * sin(angle_1_2));
				else
					new_temp_y2 = old_temp_y2;
				if (old_temp_x3 != temp_x3)
					new_temp_x3 = temp_x1 + int(i * cos(angle_1_3));
				else
					new_temp_x3 = old_temp_x3;
				if (old_temp_y3 != temp_y3)
					new_temp_y3 = temp_y1 + int(i * sin(angle_1_3));
				else
					new_temp_y3 = old_temp_y3;

				if (old_temp_x2 != new_temp_x2 || old_temp_y2 != new_temp_y2 || old_temp_x3 != new_temp_x3 || old_temp_y3 != new_temp_y3) {
					old_temp_x2 = new_temp_x2;
					old_temp_y2 = new_temp_y2;
					old_temp_x3 = new_temp_x3;
					old_temp_y3 = new_temp_y3;
					hdc_line(new_temp_x2, new_temp_y2, new_temp_x3, new_temp_y3, 2, RGB_value);
				}
			}
		}
	}
}

/***************************************************************************
  函数名称：
  功    能：给出左上角坐标及宽度、高度，画出一个长方形
  输入参数：const int left_up_x			：左上角x
			const int left_up_y			：左上角y
			const int width				：宽度
			const int high				：高度
			const int rotation_angles	：以左上角为支点，与x轴的旋转倾角（向下转为正）
			bool filled					：是否需要填充（有缺省值）
			const int thickness			：边的粗细（有缺省值）
			const int RGB_value			：颜色（有缺省值）
  返 回 值：
  说    明：
***************************************************************************/
void hdc_rectangle(const int left_up_x, const int left_up_y, const int width, const int high, const int rotation_angles, const bool filled, const int thickness, const int RGB_value)
{
	int x1 = 0, y1 = 0, x2 = 0, y2 = 0, x3 = 0, y3 = 0, x4 = 0, y4 = 0;
	x1 = left_up_x, y1 = left_up_y;
	x2 = left_up_x + int(width * cos(rotation_angles * PI / 180));
	y2 = left_up_y + int(width * sin(rotation_angles * PI / 180));
	x3 = left_up_x + int(high * cos(PI/2+ rotation_angles * PI / 180));
	y3 = left_up_y + int(high * sin(PI/2+ rotation_angles * PI / 180));
	x4 = x2 + int(high * cos(PI / 2 + rotation_angles * PI / 180));
	y4 = y2 + int(high * sin(PI / 2 + rotation_angles * PI / 180));

	hdc_line(x1, y1, x2, y2, thickness, RGB_value);
	hdc_line(x1, y1, x3, y3, thickness, RGB_value);
	hdc_line(x2, y2, x4, y4, thickness, RGB_value);
	hdc_line(x3, y3, x4, y4, thickness, RGB_value);

	int new_x3 = INT_MAX, new_x4 = INT_MAX, new_y3 = INT_MAX, new_y4 = INT_MAX;
	int old_x3 = INT_MAX, old_x4 = INT_MAX, old_y3 = INT_MAX, old_y4 = INT_MAX;

	if (filled) {
		for (int i = 1; old_x3 != x3 || old_y3 != y3 || old_x4 != x4 || old_y4 != y4; i++) {
			if (old_x3 != x3)
				new_x3 = x1 + int(i * cos(PI / 2 + rotation_angles * PI / 180));
			else
				new_x3 = old_x3;
			if (old_y3 != y3)
				new_y3 = y1 + int(i * sin(PI / 2 + rotation_angles * PI / 180));
			else
				new_y3 = old_y3;
			if (old_x4 != x4)
				new_x4 = x2 + int(i * cos(PI / 2 + rotation_angles * PI / 180));
			else
				new_x4 = old_x4;
			if (old_y4 != y4)
				new_y4 = y2 + int(i * sin(PI / 2 + rotation_angles * PI / 180));
			else
				new_y4 = old_y4;

			if (old_x3 != new_x3 || old_y3 != new_y3 || old_x4 != new_x4 || old_y4 != new_y4) {
				old_x3 = new_x3;
				old_y3 = new_y3;
				old_x4 = new_x4;
				old_y4 = new_y4;
				hdc_line(new_x3, new_y3, new_x4, new_y4, thickness, RGB_value);
			}
		}
	}
}

/***************************************************************************
  函数名称：
  功    能：给出左上角坐标及边长，画出一个长方形
  输入参数：const int left_up_x			：左上角x
			const int left_up_y			：左上角y
			const int length			：边长
			const int rotation_angles	：以左上角为支点，与x轴的旋转倾角（向下转为正）（有缺省值）
			const bool filled			：是否需要填充（有缺省值）
			const int thickness			：边的粗细（有缺省值）
			const int RGB_value			：颜色（有缺省值）
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void hdc_square(const int left_up_x, const int left_up_y, const int length, const int rotation_angles, const bool filled, const int thickness, const int RGB_value)
{
	hdc_rectangle(left_up_x, left_up_y, length, length, rotation_angles, filled, thickness, RGB_value);
}

/***************************************************************************
  函数名称：
  功    能：按照给出的参数画一段圆弧
  输入参数：const int point_x		：圆心的x
			const int point_y		：圆心的y
			const int radius		：半径
			const int angle_begin	：起始角度（以圆的最上方为0°，顺时针为正，注意：与系统坐标差了180°!!!）（有缺省值）
			const int angle_end		：结束角度（同上）（有缺省值）
			const int thickness		：粗细（有缺省值）
			const int RGB_value		：颜色（有缺省值）
  返 回 值：
  说    明：
***************************************************************************/
void hdc_arc(const int point_x, const int point_y, const int radius, const int angle_begin, const int angle_end, const int thickness, const int RGB_value)
{
	int temp_x = 0, temp_y = 0, old_x = INT_MAX, old_y = INT_MAX;
	int level = 0, delta_angle = angle_end - angle_begin;

	while (delta_angle <= 0) {
		delta_angle += 360;
	}
	while (delta_angle > 360) {
		delta_angle -= 360;
	}

	old_x = point_x + (int)(radius * sin(angle_begin * PI / 180));
	old_y = point_y - (int)(radius * cos(angle_begin * PI / 180));

	for (int i = 1; i <= delta_angle; i++) {
		temp_x = point_x + (int)(radius * sin((angle_begin + i) * PI / 180));
		temp_y = point_y - (int)(radius * cos((angle_begin + i) * PI / 180));

		if (old_x != temp_x || old_y != temp_y) {
			hdc_line(old_x, old_y, temp_x, temp_y, thickness, RGB_value);
			old_x = temp_x;
			old_y = temp_y;
			if (i == 1 || i == delta_angle - 1) {
				hdc_point(temp_x, temp_y, thickness, RGB_value);
			}
		}
	}
}

/***************************************************************************
  函数名称：
  功    能：按照给出的参数画一个扇形
  输入参数：const int point_x		：圆心的x
			const int point_y		：圆心的y
			const int radius		：半径
			const int angle_begin	：起始角度（以圆的最上方为0°，顺时针为正，注意：与系统坐标差了180°!!!）（有缺省值）
			const int angle_end		：结束角度（同上）（有缺省值）
			const bool filled		：是否需要填充（有缺省值）
			const int thickness		：粗细（有缺省值）
			const int RGB_value		：颜色（有缺省值）
  输入参数：
  返 回 值：
  说    明：当起始/结束角度差值为360的倍数时，不画两条边
***************************************************************************/
void hdc_sector(const int point_x, const int point_y, const int radius, const int angle_begin, const int angle_end, const bool filled, const int thickness, const int RGB_value)
{
	int temp_x = 0, temp_y = 0, delta_angle = angle_end - angle_begin;
	int old_x = INT_MAX, old_y = INT_MAX;

	while (delta_angle <= 0) {
		delta_angle += 360;
	}
	while (delta_angle > 360) {
		delta_angle -= 360;
	}

	hdc_arc(point_x, point_y, radius, angle_begin, angle_end, thickness, RGB_value);
	
	if (abs(angle_end - angle_begin) % 360) {
		temp_x = point_x + (int)(radius * sin(angle_begin * PI / 180));
		temp_y = point_y - (int)(radius * cos(angle_begin * PI / 180));
		hdc_line(point_x, point_y, temp_x, temp_y, thickness, RGB_value);
		temp_x = point_x + (int)(radius * sin(angle_end * PI / 180));
		temp_y = point_y - (int)(radius * cos(angle_end * PI / 180));
		hdc_line(point_x, point_y, temp_x, temp_y, thickness, RGB_value);
	}

	if (filled) {
		if (delta_angle <= 180) {
			for (int i = 0; i * 0.5 <= delta_angle; i++) {
				old_x = int(point_x + sin((angle_begin + i * 0.5) * PI / 180) * radius);
				old_y = int(point_y - cos((angle_begin + i * 0.5) * PI / 180) * radius);
				temp_x = int(point_x + sin((angle_end - i * 0.5) * PI / 180) * radius);
				temp_y = int(point_y - cos((angle_end - i * 0.5) * PI / 180) * radius);
				hdc_line(old_x, old_y, temp_x, temp_y, 4, RGB_value);
			}
			hdc_triangle(point_x, point_y, int(point_x + radius * sin(angle_begin * PI / 180)), int(point_y - radius * cos(angle_begin * PI / 180)), int(point_x + radius * sin(angle_end * PI / 180)), int(point_y - radius * cos(angle_end * PI / 180)), 1, thickness, RGB_value);
		}
		else if (delta_angle > 180 && delta_angle <= 360) {
			for (int i = 0; i * 0.5 <= 180; i++) {
				old_x = int(point_x + sin((angle_begin + i * 0.5) * PI / 180) * radius);
				old_y = int(point_y - cos((angle_begin + i * 0.5) * PI / 180) * radius);
				temp_x = int(point_x + sin((angle_begin + 180 - i * 0.5) * PI / 180) * radius);
				temp_y = int(point_y - cos((angle_begin + 180 - i * 0.5) * PI / 180) * radius);
				hdc_line(old_x, old_y, temp_x, temp_y, 4, RGB_value);
			}

			for (int i = 0; i * 0.5 <= delta_angle - 180; i++) {
				old_x = int(point_x + sin((angle_begin + 180 + i * 0.5) * PI / 180) * radius);
				old_y = int(point_y - cos((angle_begin + 180 + i * 0.5) * PI / 180) * radius);
				temp_x = int(point_x + sin((angle_end - i * 0.5) * PI / 180) * radius);
				temp_y = int(point_y - cos((angle_end - i * 0.5) * PI / 180) * radius);
				hdc_line(old_x, old_y, temp_x, temp_y, 4, RGB_value);
			}
			hdc_triangle(point_x, point_y, int(point_x + radius * sin(angle_begin * PI / 180 + PI)), int(point_y - radius * cos(angle_begin * PI / 180 + PI)), int(point_x + radius * sin(angle_end * PI / 180)), int(point_y - radius * cos(angle_end * PI / 180)), 1, thickness, RGB_value);
		}
	}
}

/***************************************************************************
  函数名称：
  功    能：按照给出的参数画一个圆
  输入参数：const int point_x		：圆心的x
			const int point_y		：圆心的y
			const int radius		：半径
			const bool filled		：是否需要填充（有缺省值）
			const int thickness		：粗细（有缺省值）
			const int RGB_value		：颜色（有缺省值）
  返 回 值：
  说    明：
***************************************************************************/
void hdc_circle(const int point_x, const int point_y, const int radius, const bool filled, const int thickness, const int RGB_value)
{
	hdc_sector(point_x, point_y, radius, 0, 360, filled, thickness, RGB_value);
}

/***************************************************************************
  函数名称：
  功    能：按照给出的参数画一个椭圆
  输入参数：const int point_x			：圆心的x
			const int point_y			：圆心的y
			const int radius_a			：平行于X轴的半径
			const int radius_b			：平行于Y轴的半径
			const int rotation_angles	：以圆心为支点，与x轴的旋转倾角（向下转为正）（有缺省值）
			const bool filled			：是否需要填充（有缺省值）
			const int thickness			：粗细（有缺省值）
			const int RGB_value			：颜色（有缺省值）
  返 回 值：
  说    明：
***************************************************************************/
void hdc_ellipse(const int point_x, const int point_y, const int radius_a, const int radius_b, const int rotation_angles, const bool filled, const int thickness, const int RGB_value)
{
	double radius_c = 0, e = 0, temp_upper_r = 0, delta_x = 0, radius = 0;
	int focus_x = 0, focus_y = 0;
	int temp_x = INT_MAX, temp_y = INT_MAX, old_x = INT_MAX, old_y = INT_MAX;
	
	if (radius_a < radius_b) {
		radius_c = sqrt(double(radius_b * radius_b - radius_a * radius_a));
		e = radius_c / radius_b;
		temp_upper_r = radius_b * (1 - e * e);
		focus_x = int(point_x - radius_c * sin(rotation_angles * PI / 180));
		focus_y = int(point_y + radius_c * cos(rotation_angles * PI / 180));
		old_x = int(focus_x - sin((0 - rotation_angles) * PI / 180) * temp_upper_r / (1 - e * cos(0)));
		old_y = int(focus_y - cos((0 - rotation_angles) * PI / 180) * temp_upper_r / (1 - e * cos(0)));

		for (int angle = 1; angle <= 360; angle++) {
			temp_x = int(focus_x - sin((angle - rotation_angles) * PI / 180) * temp_upper_r / (1 - e * cos(angle * PI / 180)));
			temp_y = int(focus_y - cos((angle - rotation_angles) * PI / 180) * temp_upper_r / (1 - e * cos(angle * PI / 180)));

			if (old_x != temp_x || old_y != temp_y) {
				hdc_line(old_x, old_y, temp_x, temp_y, thickness, RGB_value);
				old_x = temp_x;
				old_y = temp_y;
			}
		}

		if (filled) {
			for (int angle = 0; angle <= 360; angle += 1) {
				radius = temp_upper_r / (1 - e * cos(angle * PI / 180));
				old_x = int(focus_x - sin((angle - rotation_angles) * PI / 180) * radius);
				old_y = int(focus_y - cos((angle - rotation_angles) * PI / 180) * radius);
				temp_x = int(old_x + 2 * (radius_c - radius * cos(angle * PI / 180)) * sin(rotation_angles * PI / 180));
				temp_y = int(old_y - 2 * (radius_c - radius * cos(angle * PI / 180)) * cos(rotation_angles * PI / 180));
				hdc_line(old_x, old_y, temp_x, temp_y, 4, RGB_value);
			}
		}
	}
	else if (radius_a > radius_b) {
		radius_c = sqrt(double(radius_a * radius_a - radius_b * radius_b));
		e = radius_c / radius_a;
		temp_upper_r = radius_a * (1 - e * e);
		focus_x = int(point_x - radius_c * cos(rotation_angles * PI / 180));
		focus_y = int(point_y - radius_c * sin(rotation_angles * PI / 180));
		old_x = int(focus_x + cos((0 - rotation_angles) * PI / 180) * temp_upper_r / (1 - e * cos(0)));
		old_y = int(focus_y - sin((0 - rotation_angles) * PI / 180) * temp_upper_r / (1 - e * cos(0)));

		for (int angle = 1; angle <= 360; angle++) {
			temp_x = int(focus_x + cos((angle - rotation_angles) * PI / 180) * temp_upper_r / (1 - e * cos(angle * PI / 180)));
			temp_y = int(focus_y - sin((angle - rotation_angles) * PI / 180) * temp_upper_r / (1 - e * cos(angle * PI / 180)));

			if (old_x != temp_x || old_y != temp_y) {
				hdc_line(old_x, old_y, temp_x, temp_y, thickness, RGB_value);
				old_x = temp_x;
				old_y = temp_y;
			}
		}

		if (filled) {
			for (int angle = 0; angle <= 360; angle += 1) {
				radius = temp_upper_r / (1 - e * cos(angle * PI / 180));
				old_x = int(focus_x + cos((angle - rotation_angles) * PI / 180) * radius);
				old_y = int(focus_y - sin((angle - rotation_angles) * PI / 180) * radius);
				temp_x = int(old_x + 2 * (radius_c - radius * cos(angle * PI / 180)) * cos(rotation_angles * PI / 180));
				temp_y = int(old_y + 2 * (radius_c - radius * cos(angle * PI / 180)) * sin(rotation_angles * PI / 180));
				hdc_line(old_x, old_y, temp_x, temp_y, 4, RGB_value);
			}
		}
	}
}

#endif !HDC_SERIES_BY_TEACHER