/* 2154146 吴金轩 计科 */
#include <iostream>
#include <fstream>
#include <Windows.h>
#include "15-b6-bmp.h"
using namespace std;

void strcpy_tj(char* const dst, const char* const src)
{
    int i;
    for (i = 0; src[i] != '\0'; i++) {
        dst[i] = src[i];
    }
    dst[i] = 0;
}

int hex_char_to_dec_num(char arr[], int size)
{
    int dec_num = 0;
    for (int i = 0; i < size; i++) {
        dec_num |= (((unsigned int)((unsigned char)arr[i])) << (8 * i));
    }
    return dec_num;
}

bitmap_image::bitmap_image(const char* filename)
{
    ifstream infile;

    infile.open(filename, ios::in | ios::binary);
    if (infile.is_open() == 0) {
        cout << "打开文件失败！" << endl;
        exit(-1);
    }

    for (int i = 0; i < 50; i++) {
        cout << endl;
    }

    char offset_char[4] = { 0 };
    char image_type_char = { 0 };
    char width_char[4] = { 0 };
    char height_char[4] = { 0 };
    char bitmap_information[4] = { 0 };
    char num_of_index_char[4] = { 0 };
    int num_of_index = 0;

    strcpy_tj(bmp_filename, filename);

    infile.seekg(OFFSET_POS, ios::beg);
    infile.read(offset_char, 4);
    offset_byte = hex_char_to_dec_num(offset_char, 4);

    infile.seekg(WIDTH_POS, ios::beg);
    infile.read(width_char, 4);
    width_num = hex_char_to_dec_num(width_char, 4);

    infile.seekg(HEIGHT_POS, ios::beg);
    infile.read(height_char, 4);
    height_num = hex_char_to_dec_num(height_char, 4);

    infile.seekg(IMAGE_TYPE_POS, ios::beg);
    infile.read(&image_type_char, 1);
    image_type = hex_char_to_dec_num(&image_type_char, 1);

    num_of_index = (int)pow(2, image_type);

    if (image_type == 1 || image_type == 4 || image_type == 8) {
        infile.seekg(54, ios::beg);
        for (int i = 0; i < num_of_index; i++) {
            for (int j = 0; j < 4; j++) {
                infile.read(&color_index[i][j], 1);
            }
        }
    }

    infile.close();
}

int bitmap_image::width() const
{
    return width_num;
}

int bitmap_image::height() const
{
    return height_num;
}

unsigned int bitmap_image::get_pixel(int row, int col) const
{
    ifstream infile;
    color pixel_set;

    infile.open(bmp_filename, ios::in | ios::binary);
    if (infile.is_open() == 0) {
        cout << "打开文件失败！" << endl;
        exit(-1);
    }

    if (image_type == 1) {
        int num_of_byte = (width_num + 7) / 8;
        int num_of_col = (num_of_byte + 3) / 4 * 4;
        int color_offset = 0;
        char temp_index = 0;

        infile.clear();
        infile.seekg(offset_byte, ios::beg);

        color_offset = num_of_col * (height_num - row) + col / 8;
        infile.seekg(color_offset, ios::cur);
        infile.read(&temp_index, 1);
        temp_index = ((unsigned char)temp_index) >> (7 - (col % 8));
        temp_index &= 1;
        pixel_set.blue = color_index[(unsigned char)temp_index][0];
        pixel_set.green = color_index[(unsigned char)temp_index][1];
        pixel_set.red = color_index[(unsigned char)temp_index][2];
    }
    else if (image_type == 4 || image_type == 8) {
        int num_of_byte = (width_num + (8 / image_type) - 1) / (8 / image_type);
        int num_of_col = (num_of_byte + 3) / 4 * 4;
        int color_offset = 0;
        char temp_index = 0;

        infile.clear();
        infile.seekg(offset_byte, ios::beg);

        color_offset = num_of_col * (height_num - row) + col / (8 / image_type);
        infile.seekg(color_offset, ios::cur);
        infile.read(&temp_index, 1);
        if (image_type == 4) {
            temp_index = ((unsigned char)temp_index) >> (4 - (col % (8 / image_type)) * image_type);
            temp_index &= 15;
        }
        pixel_set.blue = color_index[(unsigned char)temp_index][0];
        pixel_set.green = color_index[(unsigned char)temp_index][1];
        pixel_set.red = color_index[(unsigned char)temp_index][2];
    }
    else if (image_type == 24) {
        int num_of_byte = width_num * 3;
        int num_of_col = (num_of_byte + 3) / 4 * 4;
        int color_offset = 0;
        char temp_color = 0;

        infile.clear();
        infile.seekg(offset_byte, ios::beg);

        color_offset = num_of_col * (height_num - row) + col * 3;
        infile.seekg(color_offset, ios::cur);
        infile.read(&temp_color, 1);
        pixel_set.blue = temp_color;
        infile.read(&temp_color, 1);
        pixel_set.green = temp_color;
        infile.read(&temp_color, 1);
        pixel_set.red = temp_color;
    }

    infile.close();

    return RGB(pixel_set.red, pixel_set.green, pixel_set.blue);
}