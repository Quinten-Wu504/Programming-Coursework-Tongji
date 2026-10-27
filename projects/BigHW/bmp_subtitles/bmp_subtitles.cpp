/* 2154146 吴金轩 计科 */
#include <iostream>
#include <fstream>
#include <Windows.h>
#include "bmp_subtitles.h"
#include "../include/common_string_process.h"
using namespace std;

bitmap_image::bitmap_image()
{
    bmp_filename = "";
    offset_byte = 0;
    image_type = 0;
    width_num = 0;
    height_num = 0;
}

bitmap_image::bitmap_image(string filename)
{
    ifstream infile;

    infile.open(filename, ios::in | ios::binary);
    if (infile.is_open() == 0)
    {
        cout << "打开文件失败！" << endl;
        return;
    }

    char offset_char[4] = { 0 };
    char image_type_char = { 0 };
    char width_char[4] = { 0 };
    char height_char[4] = { 0 };

    bmp_filename = filename;

    infile.seekg(OFFSET_POS, ios::beg);
    infile.read(offset_char, 4);
    offset_byte = char_to_int(offset_char, 4);

    infile.seekg(WIDTH_POS, ios::beg);
    infile.read(width_char, 4);
    width_num = char_to_int(width_char, 4);

    infile.seekg(HEIGHT_POS, ios::beg);
    infile.read(height_char, 4);
    height_num = char_to_int(height_char, 4);

    infile.seekg(IMAGE_TYPE_POS, ios::beg);
    infile.read(&image_type_char, 1);
    image_type = char_to_int(&image_type_char, 1);

    infile.close();
}

string bitmap_image::filename() const
{
    return bmp_filename;
}

int bitmap_image::width() const
{
    return width_num;
}

int bitmap_image::height() const
{
    return height_num;
}

bool bitmap_image::get_pixel_postion(int row, int col, int& byte_offset, int& bit_offset)
{
    int num_of_col = 0;
    int byte_per_row = 0;

    if (row + 16 >= height_num)
    {
        cout << "纵向越界" << endl;
        return 0;
    }
    if (col + 16 >= width_num)
    {
        cout << "横向越界" << endl;
        return 0;
    }

    if (image_type == 1 || image_type == 4 || image_type == 8)
        num_of_col = (width_num + (8 / image_type) - 1) / (8 / image_type);
    else if (image_type == 24)
        num_of_col = width_num * 3;

    byte_per_row = (num_of_col + 3) / 4 * 4;
    byte_offset = offset_byte + byte_per_row * (height_num - row - 1) + (col * image_type) / 8;
    bit_offset = (col * image_type) % 8;

    return 1;
}

void set_outfilename(bitmap_image& image, string& outfile_name)
{
    string bmp_name = image.filename();
    if (outfile_name == "")
    {
        unsigned int i = 0;
        for (i = 0; bmp_name[i] != '.'; i++)
            outfile_name += bmp_name[i];
        outfile_name += "-副本";
        for (i; i < bmp_name.length(); i++)
            outfile_name += bmp_name[i];
    }
}

void copy_bmpfile(ifstream& infile, fstream& outfile, string outfile_name)
{
    char temp_char = 0;
    infile.read(&temp_char, 1);
    while (infile.fail() != 1)
    {
        outfile.write(&temp_char, 1);
        infile.read(&temp_char, 1);
    }
}

void get_hanzi_matrix(ifstream& file, const unsigned char& area, const unsigned char& loc, char hanzi_matrix[])
{
    int code_offset = 0xA0;
    int hanzi_area = area - code_offset;
    int hanzi_loc = loc - code_offset;
    int hanzi_offset = 32 * ((hanzi_area - 1) * 94 + hanzi_loc - 1);

    file.seekg(hanzi_offset, ios::beg);
    file.read(hanzi_matrix, 32);
}

void print_captions(bitmap_image& image, string& captions, fstream& outfile, bool traditional, int posx, int posy, string color, string style)
{
    ifstream hanzi_file;
    hanzi_file.open(hanzi_filename[traditional], ios::in | ios::binary);
    if (hanzi_file.is_open() == 0) {
        cout << "打开文件失败！" << endl;
        return;
    }

    char hanzi_matrix[32] = { 0 };
    int x = 0, y = 0;

    if (captions.length() > 20)
        cout << "字幕汉字个数超过10，超出部分已截断" << endl;

    for (unsigned int i = 0; i < captions.length() && i < 20; i += 2)
    {
        bool check = 0;

        for (int j = 0; j < 32; j++)
            hanzi_matrix[j] = 0;

        get_hanzi_matrix(hanzi_file, captions[i], captions[i + 1], hanzi_matrix);
        int pixel_byte_offset = 0;
        int pixel_bit_offset = 0;
        char temp = 0;


        bool hanzi[16][16] = { 0 };
        for (int p = 0; p < 16; p++)
        {
            for (int q = 0; q < 16; q++)
            {
                unsigned one = 1 << (7 - (q % 8));
                hanzi[p][q] = hanzi_matrix[(p * 16 + q) / 8] & one;
            }
        }

        for (int j = 0; j < 16; j++)
        {
            if (style == "horizontal")
            {
                check = image.get_pixel_postion(posy + j, posx + i / 2 * 16, pixel_byte_offset, pixel_bit_offset);
                if (!check)
                    break;
            }
            else if (style == "vertical")
            {
                check = image.get_pixel_postion(posy + j + i / 2 * 18, posx, pixel_byte_offset, pixel_bit_offset);
                if (!check)
                    break;
            }

            if (image.image_type == 1)
            {
                unsigned char hanzi_pixel_1 = 0;
                unsigned char hanzi_pixel_2 = 0;

                outfile.clear();
                hanzi_pixel_1 = ~hanzi_matrix[j * 16 / 8];
                hanzi_pixel_1 = hanzi_pixel_1 >> pixel_bit_offset;
                outfile.seekg(pixel_byte_offset, ios::beg);
                temp = outfile.peek();
                hanzi_pixel_2 = temp;
                hanzi_pixel_2 = hanzi_pixel_2 >> (8 - pixel_bit_offset);
                hanzi_pixel_2 = hanzi_pixel_2 << (8 - pixel_bit_offset);
                temp = hanzi_pixel_1 + hanzi_pixel_2;
                outfile.seekp(pixel_byte_offset, ios::beg);
                outfile.write(&temp, 1);

                hanzi_pixel_1 = ~hanzi_matrix[j * 16 / 8];
                hanzi_pixel_1 = hanzi_pixel_1 << (8 - pixel_bit_offset);
                outfile.seekg(pixel_byte_offset + 1, ios::beg);
                temp = outfile.peek();
                hanzi_pixel_2 = ~hanzi_matrix[j * 16 / 8 + 1];
                hanzi_pixel_2 = hanzi_pixel_2 >> pixel_bit_offset;
                temp = hanzi_pixel_1 + hanzi_pixel_2;
                outfile.seekp(pixel_byte_offset + 1, ios::beg);
                outfile.write(&temp, 1);

                hanzi_pixel_1 = ~hanzi_matrix[j * 16 / 8 + 1];
                hanzi_pixel_1 = hanzi_pixel_1 << (8 - pixel_bit_offset);
                outfile.seekg(pixel_byte_offset + 2, ios::beg);
                temp = outfile.peek();
                hanzi_pixel_2 = temp;
                hanzi_pixel_2 = hanzi_pixel_2 << pixel_bit_offset;
                hanzi_pixel_2 = hanzi_pixel_2 >> pixel_bit_offset;
                temp = hanzi_pixel_1 + hanzi_pixel_2;
                outfile.seekp(pixel_byte_offset + 2, ios::beg);
                outfile.write(&temp, 1);
            }
            else if (image.image_type == 4)
            {
                outfile.clear();
                outfile.seekg(pixel_byte_offset, ios::beg);

                unsigned char hanzi_pixel_1 = 0;
                unsigned char hanzi_pixel_2 = 0;

                if (pixel_bit_offset == 4)
                {
                    outfile.seekg(pixel_byte_offset, ios::beg);
                    temp = outfile.peek();
                    hanzi_pixel_1 = ((unsigned char)temp >> 4 << 4);
                    hanzi_pixel_2 = hanzi[j][0] ? 0 : ((unsigned char)(temp << 4) >> 4);
                    temp = hanzi_pixel_1 + hanzi_pixel_2;
                    outfile.clear();
                    outfile.seekp(pixel_byte_offset, ios::beg);
                    outfile.write(&temp, 1);
                }

                for (int p = (pixel_bit_offset == 4); p < 15; p += 2)
                {
                    outfile.seekg(pixel_byte_offset + p / 2 + (pixel_bit_offset == 4), ios::beg);
                    temp = outfile.peek();
                    hanzi_pixel_1 = hanzi[j][p] ? 0 : ((unsigned char)temp >> 4 << 4);
                    hanzi_pixel_2 = hanzi[j][p + 1] ? 0 : ((unsigned char)(temp << 4) >> 4);
                    temp = hanzi_pixel_1 + hanzi_pixel_2;
                    outfile.clear();
                    outfile.seekp(pixel_byte_offset + p / 2 + (pixel_bit_offset == 4), ios::beg);
                    outfile.write(&temp, 1);
                }

                if (pixel_bit_offset == 4)
                {
                    outfile.seekg(pixel_byte_offset + 8, ios::beg);
                    temp = outfile.peek();
                    hanzi_pixel_1 = hanzi[j][15] ? 0 : ((unsigned char)temp >> 4 << 4);
                    hanzi_pixel_2 = (unsigned char)(temp << 4) >> 4;
                    temp = hanzi_pixel_1 + hanzi_pixel_2;
                    outfile.clear();
                    outfile.seekp(pixel_byte_offset + 8, ios::beg);
                    outfile.write(&temp, 1);
                }
            }
            else if (image.image_type == 8 || image.image_type == 24)
            {
                outfile.seekp(pixel_byte_offset, ios::beg);

                for (int k = 0; k < 16; k++)
                {
                    if (hanzi[j][k])
                    {
                        for (int p = 0; p < image.image_type / 8; p++)
                        {
                            if (image.image_type == 8)
                                temp = 0;
                            else if (image.image_type == 24)
                                temp = hex_str_to_dec_num(&(color.c_str())[4 - 2 * p], 2);
                            
                            outfile.write(&temp, 1);
                        }
                    }
                    else
                    {
                        for (int p = 0; p < image.image_type / 8; p++)
                            outfile.seekp(1, ios::cur);
                    }
                }
            }
        }
        
        if (!check)
            break;
    }

    hanzi_file.close();
}