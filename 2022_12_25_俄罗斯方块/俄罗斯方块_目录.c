#define _CRT_SECURE_NO_WARNINGS
#include "俄罗斯方块.h"
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
int flag = 10;
void menu()//打印菜单
{
	system("mode con cols=40 lines=21");
	char menu_board[20][41] =
	{ "                                        ",
	  "  ***** ***** ***** ***** ***** *****   ",
	  "    *   *       *   *   *   *   *       ",
	  "    *   *****   *   *****   *   *****   ",
	  "    *   *       *   *  *    *       *   ",
	  "    *   *****   *   *   * ***** *****   ",
	  "                中文版                  ",
	  "                                        ",
	  "                                        ",
	  "                                        ",
	  "               开始游戏                 ",
	  "               历史记录                 ",
	  "               玩法说明                 ",
	  "               作者的话                 ",
	  "                 设置                   ",
	  "               退出游戏                 ",
	  "                                        ",
	  "                                        ",
	  "                                        ",
	  "             [Tab]进行选择              ", };
	system("cls");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x79);
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 41; j++)
		{
			if (menu_board[i][j] != '*')
				printf("%c", menu_board[i][j]);
			else
			{
				printf("\33[44m ");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x79);
			}
		}
		printf("\n");
	}
	printf("                                        ");
	printf("\33[0m\r");
	flag = 10;//此处防止返回目录时出现bug
	printf("\33[10A");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x69);
	for (int j = 0; j < 41; j++)
	{
			printf("%c",menu_board[flag][j]);
	}
	printf("\33[0m");
	choose(menu_board);
}
void choose(char menu_board[20][41])//进行选择
{
	while (_kbhit())
	{
		_getch();
	}
	printf("\33[?25l");
	for (;;)
	{
		if (_kbhit())
		{
			if (GetAsyncKeyState(VK_UP))
			{
				Beep(2000, 200);
				if (flag > 10 && flag < 16)
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x79);
					printf("\r%s\r", menu_board[flag]);
					flag--;
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x69);
					printf("\33[1A");
					printf("\r\33[5m%s\r", menu_board[flag]);
				}
				else if (flag == 10)
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x79);
					printf("\r%s\r", menu_board[flag]);
					flag = 15;
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x69);
					printf("\33[5B");
					printf("\r\33[5m%s\r", menu_board[flag]);
				}
			}
			if (GetAsyncKeyState(VK_DOWN))
			{
				Beep(2000, 200);
				if (flag > 9 && flag < 15)
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x79);
					printf("\r%s\n", menu_board[flag]);
					flag++;
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x69);
					printf("\r\33[5m%s\r", menu_board[flag]);
				}
				else if (flag == 15)
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x79);
					printf("\r%s\r", menu_board[flag]);
					flag = 10;
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x69);
					printf("\33[5A");
					printf("\r\33[5m%s\r", menu_board[flag]);
				}
			}
			if (GetAsyncKeyState(VK_TAB))
			{
				Beep(2000, 200);
				printf("\33[0m");
				switch (flag - 9)
				{
				case 1://开始
				{
					//music_one();
					game_board_new();
				}
				case 2://历史记录
				{
					history();
				}
				case 3://玩法说明
				{
					INSTRUCTIONS();
				}
				case 4://作者的话
				{
					my_words();
				}
				case 5://设置
				{
					set_up();
				}
				case 6://退出游戏
				{
					Beep(4000, 200);
					Beep(2000, 300);
					system("cls");
					printf("\33[0;0H");
					printf("\33[35;47m"); 
					for (int i = 0; i < 30; i++)
					{
						for (int j = 0; j < 20; j++)
						{
							printf("  ");
						}
						printf("\n");
					}
					printf("\33[15;14H");
					printf("游 戏 结 束");
					printf("\33[30;0H");
					exit(0);
				}
				}
			}
		}
	}

}
void my_words()//废话感慨
{
	system("mode con cols=70 lines=20");
	char c = 0;
	system("cls");
	printf("\33[35;47m");
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 70; j++)
		{
			printf(" ");
		}
		printf("\n");
	}
	FILE* fp;
	printf("\33[0;0H");
	if ((fp = fopen("tetris_words.txt", "r")) == NULL)
	{
		printf("file open is error\n");
		exit(0);
	}
	for (;!feof(fp);)
	{
		printf("%c", fgetc(fp));
		Sleep(10);
	}
	fclose(fp);
	printf("\n按[Esc]返回主界面...\n");
	printf("\33[0m");
	for (;;)
	{
		if (GetAsyncKeyState(VK_ESCAPE))
			menu();
		Sleep(1000);
	}
}
void INSTRUCTIONS()//游戏操作介绍
{
	system("mode con cols=70 lines=23");
	char c = 0;
	system("cls");
	printf("\33[35;47m");
	for (int i = 0; i < 23; i++)
	{
		for (int j = 0; j < 70; j++)
		{
			printf(" ");
		}
		printf("\n");
	}
	FILE* fp;
	printf("\33[0;0H");
	if ((fp = fopen("tetris_instructions.txt", "r")) == NULL)
	{
		printf("file open is error\n");
		exit(0);
	}
	for (; !feof(fp);)
	{
		printf("%c", fgetc(fp));
	}
	fclose(fp);
	printf("\n\n按[Esc]返回主界面...");
	printf("\33[0m");
	for (;;)
	{
		if (GetAsyncKeyState(VK_ESCAPE))
			menu();
		Sleep(1000);
	}
}
void history()//感觉数据不多，以asc格式进行文件的输入输出
{
	char _nam[20] = { 0 }, c = 0, f = 0, n = 0;
	system("mode con cols=60 lines=20");
	struct player* head=NULL, *p1, *p2,*p3;//p3为了以后的排序
	p1=p2=(struct player*)malloc(sizeof(struct player));
	printf_history(20,60);
	printf("\33[10;15H查询玩家记录         排行榜");
	printf("\33[11;15H  按[←]键          按[→]键");
	FILE* fp;
	printf("\33[0;0H");
	if ((fp = fopen("tetris_historydata.txt", "r")) == NULL)
	{
		printf("file open is error\n");
		free(p1);
		exit(0);
	}
	fscanf(fp, "%d/%d/%d %d/%d/%d %d %d %d %d %d:%d %s %s", &(p1->_date.year), &(p1->_date.month), &(p1->_date.day), &(p1->_date.hour), &(p1->_date.minute), &(p1->_date.second), &(p1->large), &(p1->speed_ini), &(p1->h), &(p1->score), &(p1->min), &(p1->se), &(p1->name), &(p1->phone));
	head = p1;
	for (; !feof(fp);)
	{	
		if(n)
		p2->next = p1;
		p2 = p1;
		p1 = (struct player*)malloc(sizeof(struct player));
		fscanf(fp,"%d/%d/%d %d/%d/%d %d %d %d %d %d:%d %s %s",&(p1->_date.year),&(p1->_date.month),&(p1->_date.day),&(p1->_date.hour),&(p1->_date.minute),&(p1->_date.second),&(p1->large),&(p1->speed_ini),&(p1->h),&(p1->score),&(p1->min),&(p1->se),&(p1->name),&(p1->phone));
		/*printf(" 游戏日期:%d/%d/%d %d:%d:%d 棋盘大小:%d 初始速度:%d 溢出高度:%d 游戏得分:%d 游戏时长:%d分%d秒 玩家名称:%s 玩家电话:%s\n", p2->_date.year, p2->_date.month, p2->_date.day, p2->_date.hour, p2->_date.minute, p2->_date.second, p2->large, p2->speed_ini, p2->h, p2->score, p2->min, p2->se, p2->name, p2->phone);*/
		n++;
		p1->last = p2;
	}
	head->last = NULL;
	p2->next = NULL;
	for (;;)
	{
		if (_kbhit())
		{
			if (GetAsyncKeyState(VK_LEFT))
			{
				goto fin;
			}
			if (GetAsyncKeyState(VK_RIGHT))
			{
				goto ran;
			}
		}
		Sleep(1000);
	}
ran:
	printf_history(50, 160);
	printf("\33[30m");
	time_t t;
	struct tm* lt;
	time(&t); //获取时间戳。 
	lt = localtime(&t);//转为时间结构。 
	p2 = p1 = head;
	if (p1 == NULL)exit(0);
	//先进行排序,大的靠前
	while (p1 != NULL)//选择排序法
	{
		while (p2 != NULL)
		{
			p2 = p2->next;
			if(p2!=NULL)
			if (p2->score > p1->score)//节点互换
			{
				if (p2->next == NULL)
				{
					p2->last->next = NULL;//之后该节点要跑到p1前
					if (p1->last == NULL)
					{
						p2->last = NULL;
						head = p2;
						p1->last = p2;
						p2->next = p1;
						p1 = p2;
						p2 = NULL;
					}
					else
					{
						p2->last = p1->last;
						p2->last->next = p2;
						p1->last = p2;
						p2->next = p1;
						p1 = p2;
						p2 = NULL;
					}


				}
				else
				{
					p3 = p2->last;//保存进度,接下来会next所以先放在last，又因为p2不为head所以不用判断
					p2->last->next = p2->next;
					p2->next->last = p2->last;
					if (p1->last == NULL)
					{
						p2->last = NULL;
						head = p2;
						p1->last = p2;
						p2->next = p1;
						p1 = p2;
						p2 = p3;
					}
					else
					{
						p2->last = p1->last;
						p2->last->next = p2;
						p1->last = p2;
						p2->next = p1;
						p1 = p2;
						p2 = p3;
					}

				}
			}
		}
		if (p1 != NULL)p1 = p1->next;
		p2 = p1;
	}
	printf("\33[1;70H日排行榜\n\n");
	p1 = head;
	for (int i = 0; (p1 != NULL) && (i < 10); p1 = p1->next)
	{
		if ((p1->_date.day == lt->tm_mday) && (p1->_date.month == lt->tm_mon + 1) && (p1->_date.year == lt->tm_year + 1900))
		{
			i++;
			printf(" 第%-2d名 游戏日期:%d/%-2d/%-2d %-2d:%-2d:%-2d 棋盘大小:%d 初始速度:%d 溢出高度:%d 游戏得分:%-10d 游戏时长:%-2d分%-2d秒 玩家名称:%-20s 玩家电话:%-13s",i,p1->_date.year, p1->_date.month, p1->_date.day, p1->_date.hour, p1->_date.minute, p1->_date.second, p1->large, p1->speed_ini, p1->h, p1->score, p1->min, p1->se, p1->name, p1->phone);
		}
	}
	printf("\33[15;70H月排行榜\n\n");
	p1 = head;
	for (int i = 0; (p1 != NULL) && (i < 10); p1 = p1->next)
	{
		if ((p1->_date.month == lt->tm_mon + 1) && (p1->_date.year == lt->tm_year + 1900))
		{
			i++;
			printf(" 第%-2d名 游戏日期:%d/%-2d/%-2d %-2d:%-2d:%-2d 棋盘大小:%d 初始速度:%d 溢出高度:%d 游戏得分:%-10d 游戏时长:%-2d分%-2d秒 玩家名称:%-20s 玩家电话:%-13s", i, p1->_date.year, p1->_date.month, p1->_date.day, p1->_date.hour, p1->_date.minute, p1->_date.second, p1->large, p1->speed_ini, p1->h, p1->score, p1->min, p1->se, p1->name, p1->phone);
		}
	}
	printf("\33[30;70H总排行榜\n\n");
	p1 = head;
	for (int i = 0; (p1 != NULL) && (i < 10); p1 = p1->next, i++)
	{
		printf(" 第%-2d名 游戏日期:%d/%-2d/%-2d %-2d:%-2d:%-2d 棋盘大小:%d 初始速度:%d 溢出高度:%d 游戏得分:%-10d 游戏时长:%-2d分%-2d秒 玩家名称:%-20s 玩家电话:%-13s",i+1, p1->_date.year, p1->_date.month, p1->_date.day, p1->_date.hour, p1->_date.minute, p1->_date.second, p1->large, p1->speed_ini, p1->h, p1->score, p1->min, p1->se, p1->name, p1->phone);
	}
	printf("\33[50;140H按[Esc]返回主界面...");
	fclose(fp);
	printf("\33[0m");
	for (;;)
	{
		if (GetAsyncKeyState(VK_ESCAPE))
		{
			p1 = p2 = head;
			if (p1 == NULL)
			{
				getchar();
				printf("error");
				exit(0);
			}
			while (p1->next != NULL)
			{
				p1 = p1->next;
				free(p2);
				p2 = p1;
			}
			free(p2);
			menu();
		}
		Sleep(1000);
	}
fin:
	printf_history(10,30);
	printf("\33[5;0H玩家名:");
	printf("\33[5;9H");
	scanf("%s",_nam);
	printf_history(50,160);
	p1 = p2 = head;
	if (p1 == NULL)exit(0);
	while (p1 != NULL)
	{
		p1 = p1->next;
		if (!strcmp(p2->name, _nam))
		{
			f++;
		}
		p2 = p1;
	}
	COORD size = { 160,f+10 };
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleScreenBufferSize(hOut,size);
	p1 = p2 = head;
	if (p1 == NULL)exit(0);
	while (p1!= NULL)
	{
		p1 = p1->next;
		if (!strcmp(p2->name, _nam))
		{
			printf(" 游戏日期:%d/%-2d/%-2d %-2d:%-2d:%-2d 棋盘大小:%d 初始速度:%d 溢出高度:%d 游戏得分:%-10d 游戏时长:%-2d分%-2d秒 玩家名称:%-20s 玩家电话:%-15s\n", p2->_date.year, p2->_date.month, p2->_date.day, p2->_date.hour, p2->_date.minute, p2->_date.second, p2->large, p2->speed_ini, p2->h, p2->score, p2->min, p2->se, p2->name, p2->phone);
			f++;
		}
		p2 = p1;
	}
	if (!f)
	{
		printf("查无此人！");
	}
	printf("\33[50;140H按[Esc]返回主界面...");
	fclose(fp);
	printf("\33[0m");
	for (;;)
	{
		if (GetAsyncKeyState(VK_ESCAPE))
		{
			p1 = p2 = head;
			if (p1 == NULL)
			{
				printf("error");
				exit(0);
			}
			while (p1->next != NULL)
			{
				p1 = p1->next;
				free(p2);
				p2 = p1;
			}
			free(p2);
			menu();
		}
		Sleep(1000);
	}
}
void printf_history(int y,int x)//负责打印灰白界面
{
	char board[32] = { 0 };
	sprintf(board, "mode con cols=%d lines=%d",x,y);
	system(board);
	system("cls");
	printf("\33[35;47m");
	for (int i = 0; i < y; i++)
	{
		for (int j = 0; j < x; j++)
		{
			printf(" ");
		}
		printf("\n");
	}
	printf("\33[0;0H");
}
