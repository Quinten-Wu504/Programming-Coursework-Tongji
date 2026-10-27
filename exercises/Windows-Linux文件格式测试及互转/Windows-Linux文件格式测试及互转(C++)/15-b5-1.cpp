/* 2154146 吴金轩 计科 */
#include <iostream>
#include <fstream>
using namespace std;

const char* const parameter[4] = { "--check", "--convert", "wtol", "ltow" };

bool strcmp_tj(const char* s1, const char* s2)
{
	bool same_or_not = 1;
	for (int i = 0; s1[i] != '\0' || s2[i] != '\0'; i++) {
		if (s1[i] != s2[i]) {
			same_or_not = 0;
			break;
		}
	}
	return same_or_not;
}

int usage(const char* const procname)
{
	cout << "Usage : " << procname << " --check 文件名 | --convert { wtol|ltow } 源文件名 目标文件名" << endl;
	cout << "        " << procname << " --check a.txt" << endl;
	cout << "        " << procname << " --convert wtol a.win.txt a.linux.txt" << endl;
	cout << "        " << procname << " --convert ltow a.linux.txt a.win.txt" << endl;
	return 0;
}

bool check_parameter(int argc, char* argv[])
{
	bool mark_check = 0;
	if (argc == 3) {
		if (strcmp_tj(argv[1], parameter[0]))
			mark_check = 1;
	}
	else if (argc == 5) {
		if (strcmp_tj(argv[1], parameter[1]) && (strcmp_tj(argv[2], parameter[2]) || strcmp_tj(argv[2], parameter[3])))
			mark_check = 1;
	}
	return mark_check;
}

bool get_file_name(int argc, char* argv[], ifstream *p_infile, ofstream *p_outfile)
{
	bool mark_check = 1;
	if (argc == 3) {
		p_infile->open(argv[2], ios::in | ios::binary);
		if (p_infile->is_open() == 0) {
			cout << "文件打开失败" << endl;
			mark_check = 0;
		}
	}
	else if (argc == 5) {
		p_infile->open(argv[3], ios::in | ios::binary);
		p_outfile->open(argv[4], ios::out | ios::binary);
		if (p_infile->is_open() == 0) {
			cout << "文件打开失败" << endl;
			if (p_outfile->is_open() != 0) {
				p_outfile->close();
			}
			mark_check = 0;
		}
		else {
			if (p_outfile->is_open() == 0) {
				cout << "文件打开失败" << endl;
				p_infile->close();
				mark_check = 0;
			}
		}
	}

	return mark_check;
}

void check_file_type(ifstream* p_infile, bool* p_mark_windows, bool* p_mark_linux)
{
	char temp_char = 0;
	p_infile->read(&temp_char, 1);
	while (p_infile->fail() != 1 && (*p_mark_linux != 1 || *p_mark_windows != 1)) {
		if (temp_char == '\n') {
			if (p_infile->tellg() != 1) {
				p_infile->seekg(-2, ios::cur);
				p_infile->read(&temp_char, 1);
				if (temp_char == '\r')
					*p_mark_windows = 1;
				else
					*p_mark_linux = 1;
				p_infile->read(&temp_char, 1);
			}
			else
				*p_mark_linux = 1;

		}
		p_infile->read(&temp_char, 1);
	}
}

void check_command(bool mark_windows, bool mark_linux)
{
	if (mark_windows == 1 && mark_linux == 0)
		cout << "Windows格式" << endl;
	else if (mark_windows == 0 && mark_linux == 1)
		cout << "Linux格式" << endl;
	else
		cout << "文件格式无法识别" << endl;
}

void convert_command(ifstream* p_infile, ofstream* p_outfile, char* argv[], bool mark_windows, bool mark_linux)
{
	char temp_char = 0;
	int num_0D = 0;

	if (strcmp_tj(argv[2], parameter[2])) {
		if (mark_windows == 1 && mark_linux == 0) {
			p_infile->clear();
			p_infile->seekg(0, ios::beg);
			p_infile->read(&temp_char, 1);

			while (p_infile->fail() != 1) {
				if (temp_char == '\r') {
					p_infile->read(&temp_char, 1);
					if (temp_char == '\n') {
						p_outfile->write(&temp_char, 1);
						num_0D++;
					}
					else if (p_infile->fail() != 1){
						p_outfile->write("\r", 1);
						p_outfile->write(&temp_char, 1);
					}
					else if (p_infile->fail() == 1) {
						p_outfile->write("\r", 1);
						break;
					}
				}
				else {
					p_outfile->write(&temp_char, 1);
				}

				p_infile->read(&temp_char, 1);
			}

			cout << "转换完成，去除" << num_0D << "个0x0D" << endl;
		}
		else
			cout << "文件格式无法识别" << endl;
	}
	else if (strcmp_tj(argv[2], parameter[3])) {
		if (mark_windows == 0 && mark_linux == 1) {
			p_infile->clear();
			p_infile->seekg(0, ios::beg);
			p_infile->read(&temp_char, 1);
			while (p_infile->fail() != 1) {
				if (temp_char == '\n') {
					p_outfile->write("\r", 1);
					num_0D++;
				}
				
				p_outfile->write(&temp_char, 1);
				p_infile->read(&temp_char, 1);
			}

			cout << "转换完成，加入" << num_0D << "个0x0D" << endl;
		}
		else
			cout << "文件格式无法识别" << endl;
	}
}

int main(int argc, char* argv[])
{
	if (((argc != 5 && argc != 3) || !check_parameter(argc, argv))) {
		usage(argv[0]);
	}
	else {
		ifstream infile;
		ofstream outfile;
		if (get_file_name(argc, argv, &infile, &outfile)) {
			bool mark_windows = 0, mark_linux = 0;
			check_file_type(&infile, &mark_windows, &mark_linux);
			
			if (argc == 3)
				check_command(mark_windows, mark_linux);
			else if (argc == 5) {
				convert_command(&infile, &outfile, argv, mark_windows, mark_linux);
			}

			infile.close();
			if (argc == 5)
				outfile.close();
		}
	}
	return 0;
}
