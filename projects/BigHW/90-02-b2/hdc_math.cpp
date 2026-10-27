/* 2154146 吴金轩 计科 */
#include "../include/cmd_hdc_tools.h"
#include <iostream>
#include <Windows.h>
using namespace std;

//颜色参数
static const int color_background = 0x00CCCCCC;
static const int color_frame = RGB(124, 185, 82);
static const int color_low_battery = RGB(199, 216, 101);
static const int color_high_battery = RGB(124, 185, 82);

//电池框架拐角处的参数值
static const int frame_arc_left_x = 155;
static const int frame_arc_right_x = 595;
static const int frame_arc_up_y = 282;
static const int frame_arc_down_y = 468;
static const int frame_arc_max_radius = 43;
static const int frame_arc_min_radius = 17;

//电池框架直线处的参数值
static const int frame_line_width = 26;
static const int frame_length = 450;
static const int frame_height = 196;
static const int frame_line_horizontal_x = 150;
static const int frame_line_horizontal_y_up = 237;
static const int frame_line_horizontal_y_down = 487;
static const int frame_line_vertical_y = 277;
static const int frame_line_vertical_x_left = 110;
static const int frame_line_vertical_x_right = 614;

//电池正极处的参数值
static const int pos_pole_height = 100;
static const int pos_pole_width = 20;
static const int pos_pole_left_up_x = frame_arc_right_x + frame_arc_max_radius;
static const int pos_pole_left_up_y = frame_line_vertical_y + frame_height / 2 - pos_pole_height / 2;
static const int pos_pole_arc_radius = 10;

//电池电量的参数值
static const int battery_width = 60;
static const int battery_delta_width = 35;
static const int battery_height = frame_arc_down_y - frame_arc_up_y;

//电量满格为5格
static const int full_charge = 5;

void hdc_draw_Mathematical_curve_2154146()
{
	hdc_cls();
	
	//获取电池电量
	int charge;
	cout << "电池图标，请输入目前的电池格数（电量满格为5格，请输入1-5，默认5格）： ";
	cin >> charge;
	if (cin.fail() || charge < 1 || charge > full_charge)\
		charge = full_charge;
	cout << "电池电量为 " << charge << " 格";

	//电池主体
	hdc_rectangle(frame_line_horizontal_x, frame_line_horizontal_y_up, frame_length, frame_line_width, 0, 1, 1, color_frame);
	hdc_rectangle(frame_line_horizontal_x, frame_line_horizontal_y_down, frame_length, frame_line_width, 0, 1, 1, color_frame);

	hdc_sector(frame_arc_left_x, frame_arc_up_y, frame_arc_max_radius, 270, 360, 1, 1, color_frame);
	hdc_sector(frame_arc_left_x, frame_arc_up_y, frame_arc_min_radius, 0, 360, 1, 1, color_background);
	hdc_rectangle(frame_line_vertical_x_left, frame_line_vertical_y, frame_line_width, frame_height, 0, 1, 1, color_frame);
	hdc_sector(frame_arc_left_x, frame_arc_down_y, frame_arc_max_radius, 180, 270, 1, 1, color_frame);
	hdc_sector(frame_arc_left_x, frame_arc_down_y, frame_arc_min_radius, 0, 360, 1, 1, color_background);

	hdc_sector(frame_arc_right_x, frame_arc_up_y, frame_arc_max_radius, 0, 90, 1, 1, color_frame);
	hdc_sector(frame_arc_right_x, frame_arc_up_y, frame_arc_min_radius, 0, 360, 1, 1, color_background);
	hdc_rectangle(frame_line_vertical_x_right, frame_line_vertical_y, frame_line_width, frame_height, 0, 1, 1, color_frame);
	hdc_sector(frame_arc_right_x, frame_arc_down_y, frame_arc_max_radius, 90, 180, 1, 1, color_frame);
	hdc_sector(frame_arc_right_x, frame_arc_down_y, frame_arc_min_radius, 0, 360, 1, 1, color_background);

	//电池正极
	hdc_rectangle(pos_pole_left_up_x, pos_pole_left_up_y, pos_pole_width, pos_pole_height, 0, 1, 1, color_frame);
	hdc_sector(pos_pole_left_up_x + pos_pole_width, pos_pole_left_up_y + pos_pole_arc_radius + 1, pos_pole_arc_radius, 0, 90, 1, 1, color_frame);
	hdc_sector(pos_pole_left_up_x + pos_pole_width, pos_pole_left_up_y + pos_pole_height - pos_pole_arc_radius - 2, pos_pole_arc_radius, 90, 180, 1, 1, color_frame);
	hdc_rectangle(pos_pole_left_up_x + pos_pole_width, pos_pole_left_up_y + pos_pole_arc_radius, pos_pole_arc_radius + 1, pos_pole_height - 2 * pos_pole_arc_radius, 0, 1, 1, color_frame);

	//电池电量
	for (int i = 0; i < 5; i++) {
		if (i < charge)
			hdc_rectangle(frame_arc_left_x + i * (battery_width + battery_delta_width), frame_arc_up_y, battery_width, battery_height, 0, 1, 1, color_high_battery);
		else
			hdc_rectangle(frame_arc_left_x + i * (battery_width + battery_delta_width), frame_arc_up_y, battery_width, battery_height, 0, 1, 1, color_low_battery);
	}
}