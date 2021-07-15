#pragma once
#include <curses.h>
#include <Windows.h>
#include <string>

#define NUMDATA 5			//出力する結果の個数
#define CHARBUFF 124
#define BUFFSIZE 1024
//フィールドの設定
#define WIDTH_FIELD 60
#define HEIGHT_FIELD 30
#define NULL_FIELD 3
#define TREASURE 2
#define FIELD 1

using namespace std;

//Treasureの位置
struct treasure {
	int x_tresure;
	int y_tresure;
};

//フィールド
int field[HEIGHT_FIELD][WIDTH_FIELD];
//結果を格納
int result[NUMDATA];
int cnt = 0;
int score;
int x = 0, y = 0;
int h, w;
int i, j;
int key;

