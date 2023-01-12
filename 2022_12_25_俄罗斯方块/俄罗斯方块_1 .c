#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<Windows.h>
#include "¶íÂÞË¹·½¿é.h"
int main()
{
	music_menu();
	printf("\33[0;0H");
	printf("\33[0m;");
	printf("\33[?25l");
	menu();
	return 0;
}

