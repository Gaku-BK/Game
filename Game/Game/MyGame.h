#pragma once
#include <curses.h>
#include <Windows.h>
#include <string>

#define NUMDATA 5			//�o�͂��錋�ʂ̌�
#define CHARBUFF 124
#define BUFFSIZE 1024
//�t�B�[���h�̐ݒ�
#define WIDTH_FIELD 60
#define HEIGHT_FIELD 30
#define NULL_FIELD 3
#define TREASURE 2
#define FIELD 1

using namespace std;

//Treasure�̈ʒu
struct treasure {
	int x_tresure;
	int y_tresure;
};

//�t�B�[���h
int field[HEIGHT_FIELD][WIDTH_FIELD];
//���ʂ��i�[
int result[NUMDATA];
int cnt = 0;
int score;
int x = 0, y = 0;
int h, w;
int i, j;
int key;

