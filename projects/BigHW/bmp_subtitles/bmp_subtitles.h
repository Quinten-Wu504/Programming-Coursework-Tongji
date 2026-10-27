/* 计科 2154146 吴金轩 */

#pragma once

using namespace std;

const string hanzi_filename[2] = { "HZK16", "HZK16F" };

#define OFFSET_POS 0x0A
#define WIDTH_POS 18
#define HEIGHT_POS 22
#define IMAGE_TYPE_POS 0x1C

#define HEADER_LENGTH 14

class color
{
private:
    unsigned char blue = 0;
    unsigned char green = 0;
    unsigned char red = 0; 
};

class bitmap_image
{
private:
    string bmp_filename;
    int offset_byte;
    int image_type;
    int width_num;
    int height_num;
public:
    bitmap_image();
    bitmap_image(string filename);
    string filename() const;
    int width() const;	//返回图片的宽度
    int height() const; //返回图片的高度
    bool get_pixel_postion(int row, int col, int& byte_offset, int& bit_offset); //返回指定点的偏移字节

    friend void print_captions(bitmap_image& image, string& captions, fstream& outfile, bool traditional, int posx, int posy, string color, string style);
};

void set_outfilename(bitmap_image& image, string& outfile_name);
void copy_bmpfile(ifstream& infile, fstream& outfile, string outfile_name);
void get_hanzi_matrix(ifstream& file, const unsigned char& area, const unsigned char& loc, char hanzi_matrix[]);
