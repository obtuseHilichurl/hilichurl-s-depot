#include "俄罗斯方块.h"
#include<Windows.h>
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")
void music_menu()//op
{
	mciSendString(L"open one.mp3", NULL, 0, NULL);
	mciSendString(L"play one.mp3 repeat", NULL, 0, NULL);
}
void music_menu_colse()//op
{
	mciSendString(L"pause one.mp3", NULL, 0, NULL);
	mciSendString(L"close one.mp3", NULL, 0, NULL);
}
void music_play()//ep
{
	mciSendString(L"open two.mp3", NULL, 0, NULL);
	mciSendString(L"play two.mp3 repeat", NULL, 0, NULL);
}
void music_play_close()//ep
{
	mciSendString(L"pause two.mp3", NULL, 0, NULL);
	mciSendString(L"close two.mp3", NULL, 0, NULL);
}