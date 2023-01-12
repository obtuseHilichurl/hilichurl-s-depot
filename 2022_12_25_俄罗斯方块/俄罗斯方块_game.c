#define _CRT_SECURE_NO_WARNINGS
#include "俄罗斯方块.h"
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <time.h>
int x = 0, y = 3,large=10,h=5,speed_in=2,score=0;
struct board
{
	int in_board;
	int color;
}play_board[63][53] = { 0 };
//int in_board[63][53] = { 0 };//储存状态信息:0空1定块2墙3动块
//int color[63][53] = { 0 };//储存颜色信息:0黑1红2绿3黄4蓝5紫6浅蓝7白
void game_board_new()//打印游戏界面
{
	char board[32] = { 0 };
	sprintf(board, "mode con cols=%d lines=%d", 2 * large + 26,2*large+2);
	system(board);
	for (int i = 0; i < 63; i++)
	{
		for (int j = 0; j < 53; j++)
		{
			play_board[i][j] = play_board[2][2];
		}
	}
	x = 0, y = 4,score=0;//打开游戏即初始化
	system("cls");
	for (int j = 0; j < large + 13; j++)
	{
		play_board[1][j].color = play_board[2 * large + 2][j].color = 7;
	}
	for (int i = 0; i < large + 2; i++)
	{
		play_board[1][i].in_board = play_board[2 * large + 2][i].in_board = 2;
	}
	for (int i = 2; i < 2*large + 2; i++)
	{
		play_board[i][0].in_board = play_board[i][large + 1].in_board = 2;
		play_board[i][0].color = play_board[i][large + 1].color = play_board[i][large+12].color = 7;
		for (int j = large + 2; j < large + 12; j++)
			play_board[i][j].color = 6;
	}
	for (int i = large + 3; i < large+11; i++)
		play_board[4][i].color = 2;
	for (int i = 1; i<2*large+2; i++)
	{
		for (int j = 0; j<large+13; j++)
		{
			printf("\33[%dm  ", play_board[i][j].color + 40);
		}
		printf("\n");
	}
	switch ((large - 6) / 4)
	{
	case 1: {printf("                                              ");break; }
	case 2: {printf("                                                      "); break; }
	case 3: {printf("                                                              "); break; }
	case 4: {printf("                                                                      "); break; }
	case 5: {printf("                                                                              "); break; }
	}
	printf("\33[30;46m");
	printf("\33[%d;%dH按[Esc]退出",2* large, 2 * large + 9);
	printf("\33[35;47m");
	printf("\33[%d;1H__",3 * (6-h) + 2);
	printf("\33[%d;%dH__", 3 * (6-h)+ 2,2*large+3);
	printf("\33[3;%dH\33[35;46m得分", 2 * large + 7);
	srand((unsigned int)time(NULL));
	game_play();
}
void game_play()//写个基本逻辑吧，剩下的留给函数
{
	clock_t start,finish;
	int is_end = 0, delete_row = 0, is_next = 0, n1 = rand() % 8 + 1,speed=speed_in, n2 = 0,n3=0,nm=0,r=0,flag=0;
	music_menu_colse();
	music_play();
	printf("\33[?25l");
	printf("\33[37;46m");
	printf("\33[10;%dHNEXT:", 2 * large + 6);
	start = time(NULL);
	put_score(0,speed);
	for (;!is_end&&score<1145141919810;)//当游戏未结束
	{
		flag = 0;
		n2 = n1;
		Sleep(50);
		x = rand() % (large-6) + 5;
		n1 = rand() % 8 + 1;
		//printf("\33[22;0H");//test时自己设定图案
		//scanf("%d", &n2);
		printf("\33[46m");
		printf("\33[14;%dH        ", 2 * large + 8);
		printf("\33[13;%dH        ", 2 * large + 8);
		printf("\33[13;%dH", 2 * large + 8);
		switch (n1)
		{
		case 1: {printf("\33[41m■■■■");break; }
		case 2: {printf("\33[13;%dH", 2 * large + 10); printf("\33[42m■"); printf("\33[14;%dH", 2 * large + 8); printf("\33[42m■■■");  break; }
		case 3: {printf("\33[43m■■"); printf("\33[14;%dH", 2 * large + 8);printf("\33[14;%dH",2*large+10); printf("\33[43m■■");  break; }
		case 4: {printf("\33[13;%dH",large*2+10); printf("\33[43m■■"); printf("\33[14;%dH", 2 * large + 8); printf("\33[43m■■");  break; }
		case 5: {printf("\33[45m■■"); printf("\33[14;%dH", 2 * large + 8); printf("\33[45m■■");  break; }
		case 6: {printf("\33[46m■"); break; }
		case 7: {printf("\33[44m■"); printf("\33[14;%dH", 2 * large + 8); printf("\33[44m■■■");  break; }
		case 8: {printf("\33[13;%dH",2*large+12); printf("\33[44m■"); printf("\33[14;%dH", 2 * large + 8); printf("\33[44m■■■");  break; }
		}
		for(int tim=1;!is_next;flag++)
		{
			if(nm&&!is_next)is_next=is_rl(nm,n2);
			if ((flag >=18 - speed)&& !GetAsyncKeyState(VK_DOWN) && !is_next) {is_next = auto_move(n2); flag = 0;}
			if(!is_next)is_next=is_change(&n2);
			nm = 0;
			if (GetAsyncKeyState(VK_SPACE)) { printf("\33[%d;%dH",2*large-2,2*large+5)/*此处可修改暂停位置*/; printf("\33[46m"); system("pause"); printf("\33[%d;%dH                    ", 2 * large - 2, 2 * large + 5);
			}
			if (GetAsyncKeyState(VK_LEFT)&&!is_next)nm = -1;
			if (GetAsyncKeyState(VK_RIGHT) && !is_next)nm = 1;
			if (GetAsyncKeyState(VK_DOWN) && !is_next)is_next = auto_move(n2);
			if (GetAsyncKeyState(VK_ESCAPE)) { r = 1; goto reof;};
			if (score/500>tim)
			{
				tim++;
				if(speed<18)
					speed++;
			}
			Sleep(80);
		}
		switch (n2)
		{
		case 1: { wfigure_1(1); break; }
		case 2: { wfigure_2(1); break; }
		case 3: { wfigure_3(1); break; }
		case 4: { wfigure_4(1); break; }
		case 5: { wfigure_5(1); break; }
		case 6: { wfigure_6(1); break; }
		case 7: { wfigure_7(1); break; }
		case 8: { wfigure_8(1); break; }
		case 9: { wfigure_9(1); break; }
		case 10: { wfigure_10(1); break; }
		case 11: { wfigure_11(1); break; }
		case 12: { wfigure_12(1); break; }
		case 13: { wfigure_13(1); break; }
		case 14: { wfigure_14(1); break; }
		case 15: { wfigure_15(1); break; }
		case 16: { wfigure_16(1); break; }
		case 17: { wfigure_17(1); break; }
		case 18: { wfigure_18(1); break; }
		case 19: { wfigure_19(1); break; }
		case 20: { wfigure_20(1); break; }
		}
		delete_row = is_delete();
		for (int i = 1; i < large + 1; i++)
			if (play_board[3 *(6- h)+2][i].in_board == 1)
			{
				is_end = 1;
			}
		if (delete_row)
		{
			Beep(3000, 500);
			put_score(delete_row,speed);
			delete_row = 0;
		}

		is_next = 0,y = 4;
	}
	finish = time(NULL);
	load(score, difftime(finish,start));
reof:
	if (r) 
	{ 
		printf("\33[0m");
		music_play_close();
		music_menu();
		menu(); 
	}
}
void load(int score,int ti)//保存数据
{
	int min=0, se = 0;
	while (ti >= 60)
	{
		ti -= 60;
		min++;
	}
	se = (int)ti;
	struct player per;
	system("mode con cols=80 lines=30");
	char c = 0;
	{system("cls");
	printf("\33[35;47m");
	for (int i = 0; i < 30; i++)
	{
		for (int j = 0; j < 80; j++)
		{
			printf(" ");
		}
		printf("\n");
	}
	printf("\33[0;0H"); }
	FILE* fp;
	if ((fp = fopen("tetris_historydata.txt", "a")) == NULL)
	{
		printf("file open is error\n");
		exit(0);
	}
	per.h = h, per.large = (large-6)/4, per.score = score, per.speed_ini = speed_in/2;
	printf("\33[20;0H按[Enter]进行保存...\33[0;0H");
	printf("\33[?25h");
	time_t t;
	struct tm* lt;
	time(&t); //获取时间戳。 
	lt = localtime(&t);//转为时间结构。 
	printf(" 游戏日期:%d/%d/%d %d:%d:%d", lt->tm_year + 1900, lt->tm_mon + 1, lt->tm_mday, lt->tm_hour, lt->tm_min, lt->tm_sec);
	printf("\n 棋盘大小: %d \n 初始速度: %d \n 溢出高度: %d \n 游戏得分: %d \n 游戏时长:%d分钟%d秒 \n 玩家名称:",(large-6)/4,speed_in/2,h,score,min,se);
	while (_kbhit())
	{
		_getch();
	}
	scanf("%s",per.name);
	printf(" 玩家电话:");
	getchar();//读取enter
	scanf("%[0-9]",per.phone);//若一开始就输入非数字那我也没辙。
	fprintf(fp,"\n%d/%d/%d %d/%d/%d %d %d %d %d %d:%d %s %s", lt->tm_year + 1900, lt->tm_mon + 1, lt->tm_mday, lt->tm_hour, lt->tm_min, lt->tm_sec,per.large,per.speed_ini,per.h,per.score,min,se,per.name,per.phone);
	fclose(fp);
	printf("\33[0m");
	printf("\33[?25l");
	for (;;)
	{
		if (GetAsyncKeyState(VK_RETURN))
			music_play_close();
			music_menu();
			menu();
			Sleep(1000);
	}
}
int is_rl(int nm,int n2)//负责图形的左右移动,nm判断左移还是右移
{
	int w = 0;
	switch (n2)
	{
	case 1 : if (play_board[y][x-2].in_board&& nm == -1 || (play_board[y][x+3].in_board) && nm == 1)break; {hfigure_1(); x += nm; w = wfigure_1(3); break; }
	case 2 : if ((play_board[y][x-2].in_board|| play_board[y-1][x-1].in_board) && nm == -1 || ((play_board[y][x+2].in_board|| play_board[y-1][x+1].in_board) && nm == 1))break; {hfigure_2(); x += nm; w = wfigure_2(3); break; }
	case 3 : if (((play_board[y][x-2].in_board|| play_board[y+1][x-1].in_board)&& nm == -1) || ((play_board[y][x+1].in_board|| play_board[y+1][x+2].in_board) && nm == 1))break; {hfigure_3(); x += nm; w = wfigure_3(3); break; }
	case 4 : if (((play_board[y][x-1].in_board || play_board[y+1][x-2].in_board) && nm == -1) || ((play_board[y][x+2].in_board|| play_board[y+1][x+1].in_board) && nm == 1))break; {hfigure_4(); x += nm; w = wfigure_4(3); break; }
	case 5 : if (((play_board[y][x-1].in_board || play_board[y+1][x-1].in_board ) && nm == -1) || ((play_board[y][x+2].in_board || play_board[y+1][x+2].in_board ) && nm == 1))break; {hfigure_5(); x += nm; w = wfigure_5(3); break; }
	case 6 : if ((play_board[y][x-1].in_board && nm == -1) || (play_board[y][x+1].in_board && nm == 1))break; {hfigure_6(); x += nm; w = wfigure_6(3); break; }
	case 7 : if (((play_board[y][x-2].in_board || play_board[y-1][x-2].in_board) && nm == -1) || ((play_board[y-1][x].in_board || play_board[y][x+2].in_board ) && nm == 1))break; {hfigure_7(); x += nm; w = wfigure_7(3); break; }
	case 8 : if (((play_board[y][x-2].in_board || play_board[y-1][x].in_board) && nm == -1) || ((play_board[y][x+2].in_board  || play_board[y-1][x+2].in_board ) && nm == 1))break; {hfigure_8(); x += nm; w = wfigure_8(3); break; }
	case 9 : if (((play_board[y][x-1].in_board || play_board[y-1][x-1].in_board|| play_board[y+1][x-1].in_board || play_board[y+2][x-1].in_board) && nm == -1) || ((play_board[y-1][x+1].in_board || play_board[y][x+1].in_board || play_board[y+1][x+1].in_board ||play_board[y+2][x+1].in_board) && nm == 1))break; {hfigure_9(); x += nm; w = wfigure_9(3); break; }
	case 10: if (((play_board[y-1][x-1].in_board || play_board[y][x-1].in_board || play_board[y+1][x-1].in_board) && nm == -1) || ((play_board[y-1][x+1] .in_board || play_board[y][x+2].in_board || play_board[y+1][x+1].in_board) && nm == 1))break; {hfigure_10(); x += nm; w = wfigure_10(3); break; }
	case 11: if (((play_board[y][x-2].in_board || play_board[y+1][x-1].in_board ) && nm == -1) || ((play_board[y][x+2].in_board || play_board[y+1][x+1].in_board) && nm == 1))break; {hfigure_11(); x += nm; w = wfigure_11(3); break; }
	case 12: if (((play_board[y-1][x-1].in_board || play_board[y][x-2].in_board || play_board[y+1][x-1].in_board) && nm == -1) || ((play_board[y-1][x+1].in_board || play_board[y][x+1].in_board || play_board[y+1][x+1].in_board) && nm == 1))break; {hfigure_12(); x += nm; w = wfigure_12(3); break; }
	case 13: if (((play_board[y-1][x-1].in_board || play_board[y][x-2].in_board || play_board[y+1][x-2].in_board) && nm == -1) || ((play_board[y][x+1].in_board || play_board[y-1][x+1].in_board || play_board[y+1][x].in_board) && nm == 1))break; {hfigure_13(); x += nm; w = wfigure_13(3); break; }
	case 14: if (((play_board[y-1][x-2].in_board || play_board[y][x-2].in_board|| play_board[y+1][x-1].in_board) && nm == -1) || ((play_board[y-1][x].in_board || play_board[y][x+1].in_board || play_board[y+1][x+1].in_board) && nm == 1))break; {hfigure_14(); x += nm; w = wfigure_14(3); break; }
	case 15: if (((play_board[y-1][x-1].in_board || play_board[y][x-1].in_board|| play_board[y+1][x-1].in_board) && nm == -1) || ((play_board[y-1][x+2].in_board || play_board[y][x+1].in_board || play_board[y+1][x+1].in_board) && nm == 1))break; {hfigure_15(); x += nm; w = wfigure_15(3); break; }
	case 16: if (((play_board[y][x-2].in_board || play_board[y+1][x].in_board) && nm == -1) || ((play_board[y][x+2] .in_board || play_board[y+1][x+2].in_board) && nm == 1))break; {hfigure_16(); x += nm; w = wfigure_16(3); break; }
	case 17: if (((play_board[y-1][x-1].in_board || play_board[y][x-1].in_board|| play_board[y+1][x-2].in_board) && nm == -1) || ((play_board[y-1][x+1].in_board || play_board[y][x+1].in_board || play_board[y+1][x+1].in_board) && nm == 1))break; {hfigure_17(); x += nm; w = wfigure_17(3); break; }
	case 18: if (((play_board[y-1][x-1].in_board || play_board[y][x-1].in_board|| play_board[y+1][x-1].in_board) && nm == -1) || ((play_board[y-1][x+1].in_board || play_board[y][x+1].in_board || play_board[y+1][x+2].in_board) && nm == 1))break; {hfigure_18(); x += nm; w = wfigure_18(3); break; }
	case 19: if (((play_board[y][x-2].in_board || play_board[y+1][x-2].in_board) && nm == -1) || ((play_board[y][x+2].in_board || play_board[y+1][x].in_board) && nm == 1))break; {hfigure_19(); x += nm; w = wfigure_19(3); break; }
	case 20: if (((play_board[y-1][x-2].in_board || play_board[y][x-1].in_board|| play_board[y+1][x-1].in_board) && nm == -1) || ((play_board[y-1][x+1].in_board || play_board[y][x+1].in_board || play_board[y+1][x+1].in_board) && nm == 1))break; {hfigure_20(); x += nm; w = wfigure_20(3); break; }
	default: {Beep(5000, 1000); system("cls"); printf("err!"); exit(0); }
	}
	if (!w)
		return 0;
	else
		return 1;;

}
int is_delete()//判断有无集齐一行
{
	int count = 0,i=1,j=1,flag=1;
	for (i = 2*large+1; i > 4; i--)
	{
		flag = 1;
		for (j = 1; j < large+1; j++)
		{
			if (play_board[i][j].in_board == 0)
			{
				flag = 0; 
				break;
			}
		}
		if (flag)
		{
			Sleep(200);
			delete_it(i);
			count++,i++;//i++是为了抵消i--
		}
	}
	return count;
}
void delete_it(int i)//清除本行，将上方方块信息下移
{
	for(;i>4;i--)
	for (int j = 1; j < large + 1; j++)
		play_board[i][j] = play_board[i - 1][j];
	Sleep(50);
	printf_board();
}
void printf_board()//再次打印游戏界面
{
	printf("\33[%d;0H",3*(6-h)+2);
	for (int i = 3 * (6 - h) + 2; i < 2*large+2; i++)
	{
		for (int j = 0; j < large + 2; j++)
		{
			if (play_board[i][j].in_board == 1)
				printf("\33[%dm■", play_board[i][j].color + 40);
			else
				printf("\33[%dm  ", play_board[i][j].color + 40);
		}
		printf("\n");
	}
	printf("\33[35;47m");
	printf("\33[%d;1H__", 3 * (6-h) + 2);
	printf("\33[%d;%dH__", 3 * (6-h) + 2, 2 * large + 3);
}
int auto_move(int n)//方块自动下降
{
	int w=0;
	switch (n)
	{
	case 1 : {hfigure_1(); y++; w = wfigure_1(3); break; }
	case 2 : {hfigure_2(); y++; w = wfigure_2 (3); break; }
	case 3: {hfigure_3(); y++; w = wfigure_3(3); break; }
	case 4: {hfigure_4(); y++; w = wfigure_4(3); break; }
	case 5: {hfigure_5(); y++; w = wfigure_5(3); break; }
	case 6: {hfigure_6(); y++; w = wfigure_6(3); break; }
	case 7: {hfigure_7(); y++; w = wfigure_7(3); break; }
	case 8: {hfigure_8(); y++; w = wfigure_8(3); break; }
	case 9: {hfigure_9(); y++; w = wfigure_9(3); break; }
	case 10: {hfigure_10(); y++; w = wfigure_10(3); break; }
	case 11: {hfigure_11(); y++; w = wfigure_11(3); break; }
	case 12: {hfigure_12(); y++; w = wfigure_12(3); break; }
	case 13: {hfigure_13(); y++; w = wfigure_13(3); break; }
	case 14: {hfigure_14(); y++; w = wfigure_14(3); break; }
	case 15: {hfigure_15(); y++; w = wfigure_15(3); break; }
	case 16: {hfigure_16(); y++; w = wfigure_16(3); break; }
	case 17: {hfigure_17(); y++; w = wfigure_17(3); break; }
	case 18: {hfigure_18(); y++; w = wfigure_18(3); break; }
	case 19: {hfigure_19(); y++; w = wfigure_19(3); break; }
	case 20: {hfigure_20(); y++; w = wfigure_20(3); break; }
	
	default:{Beep(5000, 1000);system("cls");printf("err!");exit(0);}
	}
	if (!w)
		return 0;
	else
		return 1;
}
int is_change(int* n2)//方块是否旋转
{
	int w=0;
	if (GetAsyncKeyState(VK_UP))
		switch (*n2)//只是改了n2，图案和in_board没改
		{
		case 1: {if ((play_board[y - 1][x].in_board == 0) && (play_board[y + 2][x].in_board == 0) && (play_board[y + 1][x].in_board == 0))
		{
			hfigure_1();
			w=wfigure_9(3);
			*n2 = 9;
			return w;
		} }
		case 2: {if (play_board[y + 1][x].in_board == 0)
		{
			hfigure_2();
			w=wfigure_10(3);
			*n2 = 10;
			return w;
		}
		}
		case 3: {if ((play_board[y + 1][x - 1].in_board == 0) && (play_board[y - 1][x].in_board == 0))
		{
			hfigure_3();
			w=wfigure_13(3);
			*n2 = 13;
			return w;
		}
		}
		case 4: {if ((play_board[y][x - 1].in_board == 0) && (play_board[y - 1][x - 1].in_board == 0))
		{
			hfigure_4();
			w=wfigure_14(3);
			*n2 = 14;
			return w;
		}
		}
		case 7: {if ((play_board[y+1][x].in_board == 0) && (play_board[y-1][x + 1].in_board == 0)&&(play_board[y-1][x].in_board ==0))
		{
			hfigure_7();
			w=wfigure_15(3);
			*n2 = 15;
			return w;
		}
		}
		case 8: {if ((play_board[y + 1][x].in_board == 0) && (play_board[y + 1][x + 1].in_board == 0) && (play_board[y - 1][x].in_board == 0))
		{
			hfigure_8();
			w=wfigure_18(3);
			*n2 = 18;
			return w;
		}  
		}
		case 9 : {if ((play_board[y][x - 1].in_board == 0) && (play_board[y][x + 2].in_board == 0) && (play_board[y][x + 1].in_board == 0))
		{
			hfigure_9();
			w=wfigure_1(3);
			*n2 = 1;
			return w;
		}
		}
		case 10: {if (play_board[y][x - 1].in_board == 0)
		{
			hfigure_10();
			w=wfigure_11(3);
			*n2 = 11;
			return w;
		}
		}
		case 11: {if (play_board[y - 1][x].in_board == 0)
		{
			hfigure_11();
			w=wfigure_12(3);
			*n2 = 12;
			return w;
		}
		}
		case 12: {if (play_board[y][x + 1].in_board == 0)
		{
			hfigure_12();
			w=wfigure_2(3);
			*n2 = 2;
			return w;
		}
		}
		case 13: {if ((play_board[y + 1][x].in_board == 0) && (play_board[y + 1][x+1].in_board == 0))
		{
			hfigure_13();
			w=wfigure_3(3);
			*n2 = 3;
			return w;
		} 
		}
		case 14: {if ((play_board[y][x+1].in_board == 0) && (play_board[y + 1][x - 1].in_board == 0))
		{
			hfigure_14();
			w=wfigure_4(3);
			*n2 = 4;
			return w;
		}
		}
		case 15: {if ((play_board[y ][x-1].in_board == 0) && (play_board[y][x + 1].in_board == 0) && (play_board[y+1][x+1].in_board == 0))
		{
			hfigure_15();
			w=wfigure_16(3);
			*n2 = 16;
			return w;
		}
		}
		case 16: {if ((play_board[y-1][x].in_board == 0) && (play_board[y+1][x].in_board == 0) && (play_board[y + 1][x - 1].in_board == 0))
		{
			hfigure_16();
			w=wfigure_17(3);
			*n2 = 17;
			return w;
		} 
		}
		case 17: {if ((play_board[y][x-1].in_board == 0) && (play_board[y-1][x-1].in_board == 0) && (play_board[y][x + 1].in_board == 0))
		{
			hfigure_17();
			w=wfigure_7(3);
			*n2 = 7;
			return w;
		}
		}
		case 18: {if ((play_board[y][x - 1].in_board == 0) && (play_board[y][x + 1].in_board == 0) && (play_board[y + 1][x - 1].in_board == 0))
		{
			hfigure_18();
			w=wfigure_19(3);
			*n2 = 19;
			return w;
		}  
		}
		case 19: {if ((play_board[y - 1][x].in_board == 0) && (play_board[y - 1][x-1].in_board == 0) && (play_board[y + 1][x].in_board == 0))
		{
			hfigure_19();
			w=wfigure_20(3);
			*n2 = 20;
			return w;
		} 
		}
		case 20: {if ((play_board[y-1][x + 1].in_board == 0) && (play_board[y ][x+1].in_board == 0) && (play_board[y][x - 1].in_board == 0))
		{
			hfigure_20();
			w=wfigure_8(3);
			*n2 = 8;
			return w;
		}
		}
		default:break;
		}
}
void put_score(int n,int speed)//计算并打印得分
{
	if(n)score += pow(2,n)*speed*(large-6);
	printf("\33[1;4;5;37;42m");
	printf("\33[4;%dH%d\33[0m",2*large+6, score);
}
//下面是图形打印
int  wfigure_1(int n)/* ■**■■ */
{
	printf("\33[%d;%dH",y,2*x-1);
	printf("\33[41m■■■■");
	for (int i = 0; i < 4; i++)
	{
		play_board[y][x + i - 1].in_board = n;
		play_board[y][x + i - 1].color = 1;
	}
	for (int i = 0; i < 4;i++)
	{
		if (play_board[y + 1][x + i - 1].in_board != 0)
			return -1;
	}
		return 0;
}                                                     /*  ■  */
int  wfigure_2(int n)    /*■**■*/
{
	printf("\33[%d;%dH", y-1,2*x+1);
	printf("\33[42m■");
	printf("\33[%d;%dH■■■", y, 2*x-1);
	play_board[y-1][x].in_board = n;
	play_board[y - 1][x].color = 2;
	for (int i = 0; i < 3; i++)
	{
		play_board[y][x + i - 1].in_board = n;
		play_board[y][x + i - 1].color = 2;
	}
	for (int i = 0; i < 3; i++)
	{
		if (play_board[y + 1][x + i-1].in_board != 0)
			return -1;
	}
		return 0;
}
int  wfigure_3(int n)    /* ■**  */
{                        /*   ■■*/
	printf("\33[%d;%dH", y, 2 * x - 1);
	printf("\33[43m■■");
	printf("\33[%d;%dH■■", y + 1, 2 * x + 1);
	for (int i = 0; i < 2; i++)
	{
		play_board[y][x - i].color = 3;
			play_board[y][x - i].in_board = n;
	}
	for (int i = 0; i < 2; i++)
	{
		play_board[y + 1][x + i].in_board = n;
		play_board[y + 1][x + i].color = 3;
	}
	for (int i = 0; i < 2; i++)
	{
		if (play_board[y + 2][x + i].in_board != 0)
			return -1;
	}
	if (play_board[y + 1][x-1].in_board != 0)
		return -1;
	return 0;
}
int  wfigure_4(int n)    /*   **■*/
{                   /* ■■  */
	printf("\33[%d;%dH", y, 2 * x + 1);
	printf("\33[43m■■");
	printf("\33[%d;%dH■■", y + 1, 2 * x - 1);
	for (int i = 0; i < 2; i++)
	{
		play_board[y][x+i].color = 3;
		play_board[y][x + i].in_board = n;
	}
	for (int i = 0; i < 2; i++)
	{
		play_board[y + 1][x - i].color = 3;
		play_board[y + 1][x - i].in_board = n;
	}
	for (int i = 0; i < 2; i++)
	{
		if (play_board[y + 2][x - i ].in_board != 0)
		return -1;
	}
	if (play_board[y + 1][x+1].in_board != 0)
		return -1;
	return 0;
}
int  wfigure_5(int n)   /* **■ */
{                  /* ■■ */
	printf("\33[%d;%dH", y, 2 * x + 1);
	printf("\33[45m■■");
	printf("\33[%d;%dH■■", y + 1, 2 * x + 1);
	play_board[y][x].in_board = n;
	play_board[y][x].color = 5;
	play_board[y][x + 1].in_board = n;
	play_board[y][x + 1].color = 5;
	for (int i = 0; i < 2; i++)
	{
		play_board[y + 1][x + i].color = 5;
		play_board[y + 1][x + i].in_board = n;
	}
	for (int i = 0; i < 2; i++)
	{
		if (play_board[y + 2][x + i].in_board != 0)
			return -1;
	}
	return 0;
}
int  wfigure_6(int n)     /*  **  */
{
	printf("\33[%d;%dH", y, 2 * x + 1);
	printf("\33[46m■");
	play_board[y][x].in_board = n;
	play_board[y][x].color = 6;
	if (play_board[y + 1][x].in_board != 0)
		return -1;
	return 0;
}
int  wfigure_7(int n)     /*■    */
{                   /* ■**■*/
	printf("\33[%d;%dH", y-1, 2 * x - 1);
	printf("\33[44m■");
	printf("\33[%d;%dH■■■", y, 2 * x - 1);
	play_board[y-1][x-1].in_board = n;
	play_board[y - 1][x - 1].color = 4;
	for (int i = 0; i < 3; i++)
	{
		play_board[y][x + i - 1].color = 3;
		play_board[y][x + i - 1].in_board = n;
	}
	for (int i = 0; i < 3; i++)
	{
		if (play_board[y + 1][x + i-1].in_board != 0)
			return -1;
	}
		return 0;
}
int  wfigure_8(int n)     /*    ■ */
{                    /*■**■ */
	printf("\33[%d;%dH", y-1, 2 * x + 3);
	printf("\33[44m■");
	printf("\33[%d;%dH■■■", y, 2 * x -1);
	play_board[y-1][x+1].in_board = n;
	play_board[y - 1][x + 1].color = 4;
	for (int i = 0; i < 3; i++)
	{
		play_board[y][x + i - 1].color = 4;
		play_board[y][x + i - 1].in_board = n;
	}
		for (int i = 0; i < 3; i++)
	{
		if (play_board[y + 1][x + i-1].in_board != 0)
			return -1;
	}
	return 0;
}
int  wfigure_9(int n)/*竖的四点*/
{
	printf("\33[41m");
	for (int i = 0; i < 4; i++)
		printf("\33[%d;%dH■", y + i - 1, 2 * x + 1);
	for (int i = 0; i < 4; i++)
	{
		play_board[y - 1 + i][x].color = 1;
		play_board[y + i - 1][x].in_board = n;
	}
	if (play_board[y + 3][x].in_board != 0)
		return -1;
		return 0;
}
int  wfigure_10(int n)//2的顺90
{
	printf("\33[%d;%dH", y-1, 2 * x + 1);
	printf("\33[42m■");
	printf("\33[%d;%dH■■", y, 2 *x + 1);
	printf("\33[%d;%dH■", y + 1, 2 * x + 1);
	play_board[y-1][x].in_board = n;
	play_board[y - 1][x].color = 2;
	for (int i = 0; i < 2; i++)
	{
		play_board[y][x + i].color = 2;
		play_board[y][x + i].in_board = n;
	}
	play_board[y + 1][x].in_board = 3;
	play_board[y+1][x].color = 2;
		if ((play_board[y + 2][x].in_board!=0)||(play_board[y+1][x+1].in_board!=0))
			return  -1;
		return 0;
}
int  wfigure_11(int n)//10的顺90
{
	printf("\33[%d;%dH", y, 2 * x - 1);
	printf("\33[42m■■■");
	printf("\33[%d;%dH■", y + 1, 2 * x + 1);
	play_board[y+1][x].in_board = n;
	play_board[y+1][x].color = 2;
	for (int i = 0; i < 3; i++)
	{
		play_board[y][x + i - 1].color = 2;
		play_board[y][x + i - 1].in_board = n;
	}
		if ((play_board[y + 2][x].in_board !=0)||(play_board[y+1][x-1].in_board!=0)||(play_board[y+1][x+1].in_board!=0))
		return  -1;
	return 0;
}
int  wfigure_12(int n)//11的顺90
{
	printf("\33[%d;%dH", y - 1, 2 * x +1);
	printf("\33[42m■");
	printf("\33[%d;%dH■■",y, 2 * x - 1);
	printf("\33[%d;%dH■", y + 1, 2 * x +1);
	play_board[y - 1][x].in_board = n;
	play_board[y-1][x].color = 2;
	for (int i = 0; i < 2; i++)
	{
		play_board[y][x-i].color = 2;
		play_board[y][x - i].in_board = n;
	}
	play_board[y+1][x].color = 2;
	play_board[y + 1][x] .in_board= n;
	if ((play_board[y + 2][x].in_board !=0) || (play_board[y + 1][x - 1].in_board !=0))
		return -1;
	return 0;
}
int  wfigure_13(int n)//3的顺90
{
	printf("\33[%d;%dH", y-1, 2 *x + 1);
	printf("\33[43m■");
	printf("\33[%d;%dH■■", y, 2 * x - 1);
	printf("\33[%d;%dH■", y + 1, 2 * x -1);
	play_board[y-1][x] .in_board= n;
	play_board[y-1][x].color = 3;
	play_board[y+1][x - 1].in_board = n;
	play_board[y+1][x].color = 3;
	for (int i = 0; i < 2; i++)
	{
		play_board[y][x - i].color = 3;
		play_board[y][x - i].in_board = n;
	}
	if ((play_board[y + 1][x].in_board !=0)||(play_board[y+2][x-1].in_board!=0))
		return -1;
	return 0;
}
int  wfigure_14(int n)//4的顺90
{
	printf("\33[%d;%dH", y, 2 * x -1);
	printf("\33[43m■■");
	printf("\33[%d;%dH■", y-1, 2 * x - 1);
	printf("\33[%d;%dH■", y+1, 2 *x + 1);
	play_board[y-1][x - 1].in_board = n;
	play_board[y - 1][x - 1].color = 3;
	play_board[y+1][x].in_board = n;
	play_board[y - 1][x - 1].color = 3;
	for (int i = 0; i < 2; i++)
	{
		play_board[y][x - i].color = 3;
		play_board[y][x - i].in_board = n;
	}
		if ((play_board[y + 2][x].in_board !=0)||(play_board[y+1][x-1].in_board!=0))
		return  -1;
	return 0;
}
int  wfigure_15(int n)//7的顺90
{
	printf("\33[%d;%dH", y - 1, 2 * x + 1);
	printf("\33[44m■■");
	printf("\33[%d;%dH■", y, 2 * x + 1);
	printf("\33[%d;%dH■", y + 1, 2 * x + 1);
	play_board[y - 1][x + 1].in_board = n;
	play_board[y - 1][x + 1].color = 4;
	for (int i = 0; i < 3; i++)
	{
		play_board[y + 1 - i][x].in_board = n;
		play_board[y + 1 - i][x].color = 4;
	}
	if ((play_board[y + 2][x].in_board != 0) || (play_board[y][x + 1].in_board != 0))
		return  -1;
	return 0;
}
int  wfigure_16(int n)//15的顺90
{
	printf("\33[%d;%dH", y+1, 2 *x + 3);
	printf("\33[44m■");
	printf("\33[%d;%dH■■■", y , 2 * x - 1);
	play_board[y+1][x+1].in_board = n;
	play_board[y + 1][x + 1].color = 4;
	for (int i = 0; i < 3; i++)
	{
		play_board[y][x + i - 1].color = 4;
		play_board[y][x + i - 1].in_board = n;
	}
		for (int i = 0; i < 2; i++)
	{
		if (play_board[y+1][x - i].in_board != 0)
			return -1;
	}
	if (play_board[y + 2][x+1].in_board != 0)
		return -1;
	return 0;
}
int  wfigure_17(int n)//16的顺90
{
	printf("\33[%d;%dH", y-1, 2 * x +1);
	printf("\33[44m■");
	printf("\33[%d;%dH■", y , 2 * x + 1);
	printf("\33[%d;%dH■■", y+1 , 2 * x - 1);
	play_board[y+1][x-1].in_board = n;
	play_board[y + 1][x - 1].color = 4;
	for (int i = 0; i < 3; i++)
	{
		play_board[y - i + 1][x].color = 4;
		play_board[y - i + 1][x].in_board = n;
	}
		for (int i = 0; i < 2; i++)
	{
		if (play_board[y + 2][x - i].in_board != 0)
			return -1;
	}
		return 0;
}
int  wfigure_18(int n)
{
	printf("\33[%d;%dH", y - 1, 2 * x + 1);
	printf("\33[44m■");
	printf("\33[%d;%dH■", y, 2 * x + 1);
	printf("\33[%d;%dH■■", y + 1, 2 * x + 1);
	play_board[y + 1][x + 1].in_board = n;
	play_board[y + 1][x + 1].color = 4;
	for (int i = 0; i < 3; i++)
	{
		play_board[y - i + 1][x].color = 4;
		play_board[y - i + 1][x].in_board =n;
	}
	for (int i = 0; i < 2; i++)
	{
		if (play_board[y + 2][x + i].in_board != 0)
			return -1;
	}
	return 0;
}
int  wfigure_19(int n)//18的顺90
{
	printf("\33[%d;%dH", y+1, 2 * x -1);
	printf("\33[44m■");
	printf("\33[%d;%dH■■■", y, 2 * x -1);
	play_board[y+1][x-1].in_board = n;
	play_board[y + 1][x - 1].color = 4;
	for (int i = 0; i < 3; i++)
	{
		play_board[y][x+i-1].color = 4;
		play_board[y][x + i - 1].in_board = n;
	}
	for (int i = 0; i < 2; i++)
	{
		if (play_board[y+1][x+i].in_board != 0)
			return -1;
	}
	if (play_board[y + 2][x-1].in_board != 0)return -1;
	return 0;
}
int  wfigure_20(int n)//19的顺90
{
	printf("\33[%d;%dH", y-1, 2 * x -1);
	printf("\33[44m■■");
	printf("\33[%d;%dH■", y , 2 * x +1);
	printf("\33[%d;%dH■", y + 1, 2* x +1);
	play_board[y-1][x-1].in_board = n;
	play_board[y-1][x-1].color = 4;
	for (int i = 0; i < 3; i++)
	{
		play_board[y + i - 1][x].color = 4;
		play_board[y + i - 1][x].in_board = n;
	}
	if((play_board[y+2][x].in_board != 0)||(play_board[y][x-1].in_board!=0))
		return -1;
	return 0;
}
//下面是图形影藏
int  hfigure_1()/* ■**■■ */
{
	printf("\33[%d;%dH", y, 2 * x - 1);
	printf("\33[49m        ");
	for (int i = 0; i < 4; i++)
	{
		play_board[y][x+i-1] = play_board[2][2];

	}
}                                                     /*  ■  */
int  hfigure_2()    /*■**■*/
{
	printf("\33[%d;%dH", y - 1, 2 * x + 1);
	printf("\33[49m  ");
	printf("\33[%d;%dH      ", y, 2 * x - 1);
	play_board[y - 1][x] = play_board[2][2];
	for (int i = 0; i < 3; i++)
	{
		play_board[y][x+i-1] = play_board[2][2];

	}
	
}
int  hfigure_3()    /* ■**  */
{                                 	                  /*   ■■*/
	printf("\33[%d;%dH", y, 2 * x - 1);
	printf("\33[49m    ");
	printf("\33[%d;%dH    ", y + 1, 2 *x + 1);
	for (int i = 0; i < 2; i++)
	{
		play_board[y][x - i ] = play_board[2][2];
	}
	for (int i = 0; i < 2; i++)
	{
		play_board[y+1][x + i] = play_board[2][2];

	}
}
int  hfigure_4()    /*   **■*/
{                   /* ■■  */
	printf("\33[%d;%dH", y, 2 * x + 1);
	printf("\33[49m    ");
	printf("\33[%d;%dH    ", y + 1, 2 * x - 1);
	for (int i = 0; i < 2; i++)
	{
		play_board[y][x + i] = play_board[2][2];

	}
	for (int i = 0; i < 2; i++)
		play_board[y+1][x - i ] = play_board[2][2];
}
int  hfigure_5()     /* **■  */
{                                                      /* ■■  */
	printf("\33[%d;%dH", y, 2 * x + 1);
	printf("\33[49m    ");
	printf("\33[%d;%dH    ", y + 1, 2 * x + 1);
	play_board[y][x] = play_board[2][2];
	play_board[y][x + 1] = play_board[2][2];
	for (int i = 0; i < 2; i++)
	{
		play_board[y+1][x + i] = play_board[2][2];
	}
}
int  hfigure_6()     /*  **  */
{
	printf("\33[%d;%dH", y, 2 * x + 1);
	printf("\33[49m  ");
	play_board[y][x] = play_board[2][2];


}
int  hfigure_7()     /* ■    */
{                    /* ■**■*/
	printf("\33[%d;%dH", y - 1, 2* x - 1);
	printf("\33[49m  ");
	printf("\33[%d;%dH      ", y, 2 * x - 1);
	play_board[y-1][x- 1] = play_board[2][2];
	for (int i = 0; i < 3; i++)
	{
		play_board[y][x + i - 1] = play_board[2][2];
	}
}
int  hfigure_8()     /*    ■ */
{                                                      /*■**■ */
	printf("\33[%d;%dH", y - 1, 2 * x + 3);
	printf("\33[49m  ");
	printf("\33[%d;%dH      ", y, 2 * x - 1);
	play_board[y-1][x + 1] = play_board[2][2];
	for (int i = 0; i < 3; i++)
	{
		play_board[y][x + i - 1] = play_board[2][2];
	}
}
int  hfigure_9()/*竖的四点*/
{
	printf("\33[49m");
	for (int i = 0; i < 4; i++)
		printf("\33[%d;%dH  ", y + i - 1, 2 * x + 1);
	for (int i = 0; i < 4; i++)//可以简化，懒
		play_board[y + i - 1][x] = play_board[2][2];
}
int  hfigure_10()//2的顺90
{
	printf("\33[%d;%dH", y - 1, 2 * x + 1);
	printf("\33[49m  ");
	printf("\33[%d;%dH    ", y, 2 * x + 1);
	printf("\33[%d;%dH  ", y + 1, 2 * x + 1);
	play_board[y - 1][x] = play_board[2][2];
	for (int i = 0; i < 2; i++)
		play_board[y ][x+i] = play_board[2][2];
	play_board[y + 1][x] = play_board[2][2];

}
int  hfigure_11()//10的顺90
{
	printf("\33[%d;%dH", y, 2 * x - 1);
	printf("\33[49m      ");
	printf("\33[%d;%dH  ", y + 1, 2 * x + 1);
	play_board[y + 1][x] = play_board[2][2];
	for (int i = 0; i < 3; i++)
		play_board[y][x+i-1] = play_board[2][2];
}
int  hfigure_12()//11的顺90
{
	printf("\33[%d;%dH", y - 1, 2 * x + 1);
	printf("\33[49m  ");
	printf("\33[%d;%dH    ", y, 2 * x - 1);
	printf("\33[%d;%dH  ", y + 1, 2 * x + 1);
	play_board[y - 1][x] = play_board[2][2];
	for (int i = 0; i < 2; i++)
		play_board[y][x-i] = play_board[2][2];
	play_board[y + 1][x] = play_board[2][2];

}
int  hfigure_13()//3的顺90
{
	printf("\33[%d;%dH", y - 1, 2 * x + 1);
	printf("\33[49m  ");
	printf("\33[%d;%dH    ", y, 2 * x - 1);
	printf("\33[%d;%dH  ", y + 1, 2 * x - 1);
	play_board[y- 1][x] = play_board[2][2];
	play_board[y + 1][x-1] = play_board[2][2];
	for (int i = 0; i < 2; i++)
		play_board[y][x-i] = play_board[2][2];
}
int  hfigure_14()//4的顺90
{
	printf("\33[%d;%dH", y, 2 * x - 1);
	printf("\33[49m    ");
	printf("\33[%d;%dH  ", y - 1, 2 * x - 1);
	printf("\33[%d;%dH  ", y + 1, 2 * x + 1);
	play_board[y - 1][x-1] = play_board[2][2];
	play_board[y + 1][x] = play_board[2][2];
	for (int i = 0; i < 2; i++)
		play_board[y][x-i] = play_board[2][2];
}
int  hfigure_15()//7的顺90
{
	printf("\33[%d;%dH", y - 1, 2 * x + 1);
	printf("\33[49m    "); 
	printf("\33[%d;%dH  ", y, 2 * x + 1);
	printf("\33[%d;%dH  ", y + 1, 2 * x + 1);
	play_board[y - 1][x+1] = play_board[2][2];
	for (int i = 0; i < 3; i++)
		play_board[y + 1-i][x] = play_board[2][2];
}
int  hfigure_16()//15的顺90
{
	printf("\33[%d;%dH", y + 1, 2 * x + 3);
	printf("\33[49m  ");
	printf("\33[%d;%dH      ", y, 2 * x - 1);
	play_board[y + 1][x+1] = play_board[2][2];
	for (int i = 0; i < 3; i++)
		play_board[y] [x+i-1] = play_board[2][2];
}
int  hfigure_17()//16的顺90
{
	printf("\33[%d;%dH", y + 1, 2 * x - 1);
	printf("\33[49m    ");
	printf("\33[%d;%dH  ", y, 2 * x + 1);
	printf("\33[%d;%dH  ", y - 1, 2 * x + 1);
	play_board[y - 1][x] = play_board[2][2];
	play_board[y ][x] = play_board[2][2];
	for (int i = 0; i < 2; i++)
		play_board[y + 1][x - i] = play_board[2][2];
}
int  hfigure_18()//8的顺90
{
	printf("\33[%d;%dH", y - 1, 2 * x + 1);
	printf("\33[49m  ");
	printf("\33[%d;%dH  ", y, 2 * x + 1);
	printf("\33[%d;%dH    ", y + 1, 2 * x + 1);
	play_board[y + 1][x+1] = play_board[2][2];
	for (int i = 0; i < 3; i++)
		play_board[y -i+ 1][x] = play_board[2][2];
}
int  hfigure_19()//18的顺90
{
	printf("\33[%d;%dH", y + 1, 2 * x - 1);
	printf("\33[49m  ");
	printf("\33[%d;%dH      ", y, 2 * x - 1);
	play_board[y + 1][x-1] = play_board[2][2];
	for (int i = 0; i < 3; i++)
		play_board[y][x+i-1] = play_board[2][2];
}
int  hfigure_20()//19的顺90
{
	printf("\33[%d;%dH", y - 1, 2 * x - 1);
	printf("\33[49m    ");
	printf("\33[%d;%dH  ",y, 2 * x + 1);
	printf("\33[%d;%dH  ", y + 1, 2 * x + 1);
	play_board[y - 1][x-1] = play_board[2][2];
	for (int i = 0; i < 3; i++)
		play_board[y + i-1][x] = play_board[2][2];
}
void set_up()//设置，可以调整参数
{
	system("mode con cols=40 lines=21");
	int flag = 1;
	char set_board[20][41] =
	{ "                                        ",
	  "                                        ",
	  "                                        ",
	  "初始下落速度:                           ",
	  "                                        ",
	  "                                        ",
	  "游戏界面大小:                           ",
	  "                                        ",
	  "                                        ",
	  "方块溢出高度:                           ",
	  "                                        ",
	  "                                        ",
	  "                                        ",
	  "                                        ",
	  "                                        ",
	  "           [↑][↓]进行选择             ",
	  "           [←][→]进行调整             ",
	  "                                        ",
	  "                                        ",
	  "           [Esc]键返回目录              ", };
	system("cls");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x79);
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 41; j++)
		{
				printf("%c",set_board[i][j]);
		}
		printf("\n");
	}
	printf("                                        ");
	printf("\33[34;42m");
	printf("\33[4;22H          ");
	printf("\33[7;22H          ");
	printf("\33[10;22H          ");
	printf("\33[4;22H");
	for (int i = speed_in / 2; i; i--)
		printf("■");
	printf("\33[7;22H");
	for (int i=(large-6)/4;i;i--)
		printf("■");
	printf("\33[10;22H");
	for (int i=h;i;i--)
		printf("■");
	printf("\33[37;44m");
	printf("\33[%d;1H",3*flag+1);
	for (int j = 0; j < 14; j++)
	{
		printf("%c", set_board[3*flag][j]);
	}
	while(1)
	{
		if (GetAsyncKeyState(VK_ESCAPE))
		{
			Sleep(500);
			printf("\33[0m");
			menu();
		}
		if (GetAsyncKeyState(VK_DOWN)) 
		{
			Beep(2000, 200);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x79);
			printf("\33[%d;1H", 3 * flag + 1);
			for (int j = 0; j < 14; j++)
			{
				printf("%c", set_board[3 * flag][j]);
			}
			switch (flag)
			{
			case 1: 
			{
				flag = 2;
				Sleep(100);
				break;
			}
			case 2:
			{
				flag = 3;
				Sleep(100);
				break;
			}
			case 3:
			{
				flag = 1;
				Sleep(100);
				break;
			}
			}
			printf("\33[37;44m");
			printf("\33[%d;1H", 3 * flag + 1);
			for (int j = 0; j < 14; j++)
			{
				printf("%c", set_board[3 * flag][j]);
			}
		}
		if (GetAsyncKeyState(VK_UP))
		{
			Beep(2000, 200);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x79);
			printf("\33[%d;1H", 3 * flag + 1);
			for (int j = 0; j < 14; j++)
			{
				printf("%c", set_board[3 * flag][j]);
			}
			switch (flag)
			{
			case 1:
			{
				flag = 3;
				Sleep(100);
				break;
			}
			case 2:
			{
				flag = 1;
				Sleep(100);
				break;
			}
			case 3:
			{
				flag = 2;
				Sleep(100);
				break;
			}
			}
			printf("\33[37;44m");
			printf("\33[%d;1H", 3 * flag + 1);
			for (int j = 0; j < 14; j++)
			{
				printf("%c", set_board[3 * flag][j]);
			}
		}
		if (GetAsyncKeyState(VK_RIGHT))
		{
			Beep(2000,200);
			switch (flag)
			{
				Beep(2000, 200);
			case 1:
			{
				if (speed_in < 9)
				{
					speed_in += 2;
					printf("\33[34;42m");
					printf("\33[4;%dH■",20+speed_in);
				}
				break;
			}
			case 2:
			{
				if (large < 26)
				{
					large += 4;
					printf("\33[34;42m");
					printf("\33[7;%dH■",17+large/2);
				}
				break;
			}
			case 3:
			{
				if (h < 5)
				{
					h++;
					printf("\33[34;42m");
					printf("\33[10;%dH■", 20 + 2 * h);
				}				
				break;
			}
			}
		}
		if (GetAsyncKeyState(VK_LEFT))
		{
			Beep(2000, 200);
			switch (flag)
			{
				Beep(2000, 200);
			case 1:
			{
				if (speed_in > 2)
				{
					speed_in -= 2;
					printf("\33[34;42m");
					printf("\33[4;%dH  ", 22 + speed_in);
				}
				break;
			}
			case 2:
			{
				if (large > 13)
				{
					large -= 4;
					printf("\33[34;42m");
					printf("\33[7;%dH  ", 19 + large / 2);
				}
				break;
			}
			case 3:
			{
				if (h >1)
				{
					h--;
					printf("\33[34;42m");
					printf("\33[10;%dH  ", 22 + 2 * h);
				}
				break;
			}
			}
		}
	}
	

}
