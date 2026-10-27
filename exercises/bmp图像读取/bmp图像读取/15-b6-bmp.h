/* 计科 2154146 吴金轩 */

#pragma once

#define MAX_WIDTH 768
#define MAX_HEIGHT 1366
#define OFFSET_POS 0x0A
#define WIDTH_POS 18
#define HEIGHT_POS 22
#define IMAGE_TYPE_POS 0x1C
#define NUM_OF_INDEX_POS 46

#define HEADER_LENGTH 14

class color
{
public:
    unsigned char blue = 0;
    unsigned char green = 0;
    unsigned char red = 0;
};

class bitmap_image
{
protected:
    char bmp_filename[100];
    char color_index[256][4];
    int offset_byte;
    int image_type;
    int width_num;
    int height_num;
public:
    int width() const;	//返回图片的宽度
    int height() const; //返回图片的高度
    unsigned int get_pixel(int row, int col) const; //返回指定点的RGB颜色
    bitmap_image(const char* filename);
};
