/* 2154146 吴金轩 计科1班 */
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <time.h>

using namespace std;

#ifdef __linux__
const char suit[4] = { 'C','D','H','S' };
#else
const char suit[4] = { 5,4,3,6 };
#endif

const char num_of_cards[14] = "3456789TJQKA2";

/***************************************************************************
  函数名称：
  功    能：打印某个玩家的牌面信息，如果是地主，后面加标记
  输入参数：
  返 回 值：
  说    明：
 ***************************************************************************/
int print(const char* prompt, const bool landlord, const unsigned long long player)
{
	cout << prompt;
	
	for (int i = 0; i < 54; i++) {
		if ((player & ((unsigned long long)(1) << i)) != 0) {
			if (i / 4 >= 0 && i / 4 <= 12) {
				cout << suit[i % 4] << num_of_cards[i / 4] << " ";
			}
			else if (i == 52)
				cout << "BJ ";
			else if (i == 53)
				cout << "RJ ";
		}
	}

	if (landlord) {
		cout << "(地主)";
	}

	cout << endl;

	return 0;
}

/***************************************************************************
  函数名称：
  功    能：发牌（含键盘输入地主）
  输入参数：
  返 回 值：
  说    明：
 ***************************************************************************/
int deal(unsigned long long* player)
{
	int landlord = -1;
	unsigned long long temp_cards = 0;
	unsigned int random_num = 0;
	srand((unsigned int)time(0));

	for (int i = 0; i < 17; i++) {
		cout << "第" << i + 1 << "轮结束：" << endl;
		for (int j = 0; j < 3; j++) {
			temp_cards = player[0] | player[1] | player[2];
			random_num = rand() % 54;
			while ((((unsigned long long)(1) << random_num) & temp_cards) != 0) {
				random_num = rand() % 54;
			}
			player[j] |= ((unsigned long long)(1) << random_num);
		}
		print("甲的牌：", 0, player[0]);
		print("乙的牌：", 0, player[1]);
		print("丙的牌：", 0, player[2]);
	}

	while (cin.fail() || landlord < 0 || landlord>2) {
		cout << endl;
		cout << "请选择一个地主[0-2]：" << endl;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(32767, '\n');
		}
		cin >> landlord;
	}

	temp_cards = player[0] | player[1] | player[2];
	temp_cards = ~temp_cards;
	player[landlord] = temp_cards | player[landlord];

	return landlord;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：main函数，不准修改
 ***************************************************************************/
int main()
{
	unsigned long long player[3] = { 0 }; //存放三个玩家的发牌信息
	int landlord; //返回0-2表示哪个玩家是地主

	cout << "按回车键开始发牌";
	while (getchar() != '\n')
		;

	landlord = deal(player);
	print("甲的牌：", (landlord == 0), player[0]);
	print("乙的牌：", (landlord == 1), player[1]);
	print("丙的牌：", (landlord == 2), player[2]);

	return 0;
}
