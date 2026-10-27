/* 2154146 Îâ½ðÐù ¼Æ¿Æ */
#include <Windows.h>
#include "../include/cmd_hdc_tools.h"

#define BLUE_COLOR RGB(61,155,191)
#define WHITE_COLOR RGB(240,240,240)
#define BLACK_COLOR RGB(31,31,33)
#define RED_COLOR RGB(212,65,71)
#define YELLOW_COLOR RGB(237,210,90)

static void hdc_cartoon_eyes(const int base_x, const int base_y)
{
	const int eyes_offset_x = 42;
	const int eyes_offset_y = 260;
	const int eyes_radius_a = 40;
	const int eyes_radius_b = 52;

	const int eye_balls_offset_x = 25;
	const int eye_balls_offset_y = 250;
	const int eye_balls_radius_a = 10;
	const int eye_balls_radius_b = 15;

	const int eye_highlight_offset_x = eye_balls_offset_x - 2;
	const int eye_highlight_offset_y = eye_balls_offset_y - 2;
	const int eye_highlight_radius = 2;

	//ÑÛ¾¦ÂÖÀª
	hdc_ellipse(base_x - eyes_offset_x, base_y - eyes_offset_y, eyes_radius_a, eyes_radius_b, 0, 1, 2, WHITE_COLOR);
	hdc_ellipse(base_x - eyes_offset_x, base_y - eyes_offset_y, eyes_radius_a, eyes_radius_b, 0, 0, 5, BLACK_COLOR);
	hdc_ellipse(base_x + eyes_offset_x, base_y - eyes_offset_y, eyes_radius_a, eyes_radius_b, 0, 1, 2, WHITE_COLOR);
	hdc_ellipse(base_x + eyes_offset_x, base_y - eyes_offset_y, eyes_radius_a, eyes_radius_b, 0, 0, 5, BLACK_COLOR);
	//ÑÛ¾¦Ï¸½Ú
	hdc_ellipse(base_x - eye_balls_offset_x, base_y - eye_balls_offset_y, eye_balls_radius_a, eye_balls_radius_b, 0, 1, 2, BLACK_COLOR);
	hdc_ellipse(base_x + eye_balls_offset_x, base_y - eye_balls_offset_y, eye_balls_radius_a, eye_balls_radius_b, 0, 1, 2, BLACK_COLOR);
	hdc_circle(base_x - eye_highlight_offset_x, base_y - eye_highlight_offset_y, eye_highlight_radius, 1, 2, WHITE_COLOR);
	hdc_circle(base_x + eye_highlight_offset_x, base_y - eye_highlight_offset_y, eye_highlight_radius, 1, 2, WHITE_COLOR);
}

static void hdc_cartoon_face(const int base_x, const int base_y)
{
	//±Ç×Ó
	hdc_circle(base_x, base_y - 215, 18, 1, 2, RED_COLOR);
	hdc_circle(base_x, base_y - 215, 20, 0, 5, BLACK_COLOR);
	hdc_circle(base_x - 3, base_y - 220, 4, 1, 2, WHITE_COLOR);

	//×ì°Í
	hdc_arc(base_x + 777, base_y - 130, 780, 266, 275, 5, BLACK_COLOR);
	hdc_arc(base_x, base_y - 525, 450, 165, 194, 5, BLACK_COLOR);
	hdc_arc(base_x - 98, base_y - 112, 25, 205, 390, 5, BLACK_COLOR);

	//ºú×Ó
	hdc_line(base_x + 65, base_y - 200, base_x + 170, base_y - 230, 5, BLACK_COLOR);
	hdc_line(base_x + 80, base_y - 165, base_x + 180, base_y - 170, 5, BLACK_COLOR);
	hdc_line(base_x + 85, base_y - 130, base_x + 185, base_y - 110, 5, BLACK_COLOR);

	hdc_line(base_x - 55, base_y - 200, base_x - 170, base_y - 230, 5, BLACK_COLOR);
	hdc_line(base_x - 70, base_y - 165, base_x - 180, base_y - 170, 5, BLACK_COLOR);
	hdc_line(base_x - 75, base_y - 130, base_x - 185, base_y - 110, 5, BLACK_COLOR);
}

static void hdc_cartoon_head(const int base_x, const int base_y)
{
	//¶Ç×Ó
	hdc_ellipse(base_x, base_y + 75, 130, 120, 0, 1, 2, WHITE_COLOR);
	hdc_ellipse(base_x, base_y + 75, 130, 120, 0, 0, 5, BLACK_COLOR);
	hdc_ellipse(base_x, base_y + 75, 100, 90, 0, 1, 2, WHITE_COLOR);
	hdc_ellipse(base_x, base_y + 75, 100, 90, 0, 0, 5, BLACK_COLOR);
	
	//ÄÔ´ü
	hdc_ellipse(base_x, base_y - 150, 200, 180, 0, 1, 2, BLUE_COLOR);
	hdc_ellipse(base_x, base_y - 150, 200, 180, 0, 0, 5, BLACK_COLOR);
	hdc_ellipse(base_x, base_y - 115, 180, 140, 0, 1, 2, WHITE_COLOR);
	hdc_ellipse(base_x, base_y - 115, 180, 140, 0, 0, 5, BLACK_COLOR);

	//Á³²¿Ï¸½Ú
	hdc_cartoon_eyes(base_x, base_y);
	hdc_cartoon_face(base_x, base_y);

	//¿Ú´ü
	hdc_rectangle(base_x - 105, base_y + 75 - 90, 210, 90, 0, 1, 2, WHITE_COLOR);
	hdc_line(base_x - 100, base_y + 75, base_x + 100, base_y + 75, 5, BLACK_COLOR);
}

static void hdc_cartoon_neck(const int base_x, const int base_y)
{
	//ÏîÈ¦
	for (int i = 587; i <= 612; i += 4) {
		hdc_arc(base_x, base_y - i, 600, 165, 195, 5, RED_COLOR);
	}
	hdc_arc(base_x, base_y - 587, 600, 165, 195, 5, BLACK_COLOR);
	hdc_arc(base_x, base_y - 612, 600, 165, 195, 5, BLACK_COLOR);
	hdc_arc(base_x - 117, base_y - 20, 40, 250, 290, 5, BLACK_COLOR);
	hdc_arc(base_x + 117, base_y - 20, 40, 70, 110, 5, BLACK_COLOR);

	//Áåîõ
	hdc_circle(base_x, base_y + 20, 25, 1, 2, YELLOW_COLOR);
	hdc_circle(base_x, base_y + 20, 26, 0, 5, BLACK_COLOR);
	hdc_line(base_x - 20, base_y + 8, base_x + 20, base_y + 8, 3, BLACK_COLOR);
	hdc_line(base_x - 23, base_y + 15, base_x + 23, base_y + 15, 3, BLACK_COLOR);
	hdc_circle(base_x, base_y + 27, 5, 1, 2, BLACK_COLOR);
	hdc_line(base_x, base_y + 32, base_x, base_y + 45, 3, BLACK_COLOR);
}

static void hdc_cartoon_arm(const int base_x, const int base_y)
{
	//Ë«±Û
	hdc_ellipse(base_x - 140, base_y + 62, 90, 77, -12, 1, 2, BLUE_COLOR);
	hdc_ellipse(base_x - 140, base_y + 62, 90, 77, -12, 0, 5, BLACK_COLOR);
	hdc_circle(base_x - 165, base_y + 125, 35, 1, 2, WHITE_COLOR);
	hdc_circle(base_x - 165, base_y + 125, 36, 0, 5, BLACK_COLOR);

	hdc_ellipse(base_x + 140, base_y + 62, 90, 77, 12, 1, 2, BLUE_COLOR);
	hdc_ellipse(base_x + 140, base_y + 62, 90, 77, 12, 0, 5, BLACK_COLOR);
	hdc_circle(base_x + 165, base_y + 125, 35, 1, 2, WHITE_COLOR);
	hdc_circle(base_x + 165, base_y + 125, 36, 0, 5, BLACK_COLOR);
}

static void hdc_cartoon_leg(const int base_x, const int base_y)
{
	//Ë«ÍÈ
	hdc_ellipse(base_x - 147, base_y + 145, 10, 125, -1, 1, 2, BLUE_COLOR);
	hdc_arc(base_x + 1440, base_y + 100, 1600, 264, 273, 5, BLACK_COLOR);

	hdc_ellipse(base_x + 147, base_y + 145, 10, 125, 1, 1, 2, BLUE_COLOR);
	hdc_arc(base_x - 1440, base_y + 100, 1600, 87, 96, 5, BLACK_COLOR);

	hdc_rectangle(base_x - 150, base_y + 90, 300, 130, 0, 1, 2, BLUE_COLOR);

	hdc_rectangle(base_x - 140, base_y + 220, 119, 50, 0, 1, 2, BLUE_COLOR);
	hdc_rectangle(base_x + 21, base_y + 220, 119, 50, 0, 1, 2, BLUE_COLOR);
	hdc_triangle(base_x - 21, base_y + 220, base_x - 3, base_y + 220, base_x - 21, base_y + 270, 1, 2, BLUE_COLOR);
	hdc_triangle(base_x + 21, base_y + 220, base_x + 3, base_y + 220, base_x + 21, base_y + 270, 1, 2, BLUE_COLOR);

	hdc_arc(base_x + 159, base_y + 300, 180, 279, 298, 5, BLACK_COLOR);
	hdc_arc(base_x - 159, base_y + 300, 180, 58, 81, 5, BLACK_COLOR);

	hdc_line(base_x - 150, base_y + 270, base_x - 20, base_y + 270, 5, BLACK_COLOR);
	hdc_line(base_x + 150, base_y + 270, base_x + 20, base_y + 270, 5, BLACK_COLOR);
}

static void hdc_cartoon_foot(const int base_x, const int base_y)
{
	hdc_ellipse(base_x - 85, base_y + 295, 80, 40, 0, 1, 2, WHITE_COLOR);
	hdc_ellipse(base_x - 85, base_y + 295, 80, 40, 0, 0, 5, BLACK_COLOR);

	hdc_ellipse(base_x + 85, base_y + 295, 80, 40, 0, 1, 2, WHITE_COLOR);
	hdc_ellipse(base_x + 85, base_y + 295, 80, 40, 0, 0, 5, BLACK_COLOR);
}

void hdc_draw_cartoon_2154146(const int base_x, const int base_y) 
{
	hdc_cls();

	hdc_init(14, 14, 800, 800);

	hdc_cartoon_foot(base_x, base_y);

	hdc_cartoon_arm(base_x, base_y);

	hdc_cartoon_leg(base_x, base_y);

	hdc_cartoon_head(base_x, base_y);

	hdc_cartoon_neck(base_x, base_y);
}