#include "MyGame.h"

//フィールドの表示
void draw_field() {
	//色の設定
	start_color();
	init_pair(1, COLOR_GREEN, COLOR_BLACK);		//緑
	init_pair(2, COLOR_BLUE, COLOR_BLACK);		//青
	init_pair(3, COLOR_WHITE, COLOR_BLACK);		//白
	//フィールドを描画する
	for (i = 0; i < HEIGHT_FIELD; i++) {
		for (j = 0; j < WIDTH_FIELD; j++) {
			if ((field[i][j] == FIELD) || (field[i][j] == TREASURE)) {
				attrset(COLOR_PAIR(1));
				mvaddstr(i, j, "@");
			}
			if (field[i][j] == NULL_FIELD) {
				mvaddstr(i, j, " ");
			}
			if (field[i][j] == 0) {
				attrset(COLOR_PAIR(2));
				mvaddstr(i, j, "*");
			}
		}
	}

}

//スタート画面の表示
void view_start() {
	getmaxyx(stdscr, h, w);
	attrset(COLOR_PAIR(3));
	mvaddstr(h / 2, w / 2 - 9, "PRESS S");
}

//結果画面の表示
void view_result() {
	getmaxyx(stdscr, h, w);
	attrset(COLOR_PAIR(3));
	mvaddstr(2, w / 2 - 4, "CLEAR!!!");
	mvaddstr(3, w / 2 - 9, "YOUR SCORE : ");
	mvprintw(3, w / 2 + 4, "%d", score);
	mvprintw(4, w / 2 - 4, "PRESS S");
	mvprintw(7, w / 2 - 4, "RANKING");
}

//フィールドの初期化
void reset() {
	for (i = 0; i < HEIGHT_FIELD; i++) {
		for (j = 0; j < WIDTH_FIELD; j++) {
			if ((i == 0) || (j == 0)) {
				field[i][j] = 0;
			}
			else if ((i == 29) || (j == 59)) {
				field[i][j] = 0;
			}
			else {
				field[i][j] = 1;
			}
		}
	}
}

//Treasureを見つけた時の判定
BOOLEAN check_treasure(struct treasure* tr, int x, int y) {
	int z = 0;
	for (int i = 0; i < 5; i++) {
		if ((x == (tr + i)->x_tresure) && (y == (tr + i)->y_tresure)) {
			z++;
		}
	}
	if (z != 0) {		//見つけた時
		return (TRUE);
	}
	else {
		return(FALSE);
	}

}

//スコアを計算
void count_score() {
	for (i = 0; i < HEIGHT_FIELD; i++) {
		for (j = 0; j < WIDTH_FIELD; j++) {
			if (field[i][j] == 1) {
				score++;
			}
		}
	}
}

//結果の読み込み
void read_result(int result[]) {
	FILE* fp;
	char s[BUFFSIZE];
	char* data[1];
	char* ctx;
	errno_t error;
	int none;
	error = fopen_s(&fp, "result.csv", "r");
	if (error != 0) {
		fprintf_s(stderr, "failed to open");
	}
	else {
		for (int c = 0; c < NUMDATA; c++) {
			if (fgets(s, BUFFSIZE, fp) != NULL) {
				data[0] = strtok_s(s, "", &ctx);
				result[c] = atoi(data[0]);
				cnt++;
			}
			else {
				none = 0;
			}
		}
		fclose(fp);
	}
}

//結果の書き込み
void write_result(int result[]) {
	FILE* fp;

	errno_t error;
	error = fopen_s(&fp, "result2.csv", "w");
	if (error != 0) {
		for (int f = 0; f < NUMDATA; f++) {
			fputs(to_string(result[f]).c_str(), fp);

		}

		fclose(fp);
	}
}

//現在のディレクトリを取得
void getGurrentDirectory(char* currentDirectory) {
	GetCurrentDirectory(CHARBUFF, currentDirectory);
}

//初期化ファイルの設定
void setting() {
	char currentDirectory[CHARBUFF];
	getGurrentDirectory(currentDirectory);

	char startpoint[CHARBUFF];
	sprintf_s(startpoint, "startpoint");
	char startx[CHARBUFF];
	sprintf_s(startx, "startx");
	char settingFile[CHARBUFF];
	sprintf_s(settingFile, "%s\\setting.ini", currentDirectory);
	x = GetPrivateProfileInt(startpoint, startx, -1, settingFile);
	y = x * 2;
}

//メイン関数
int main(int argc, char* avg[])
{
	//初期設定
	setting();
	
	//初期化
	initscr();
	noecho();
	cbreak();
	keypad(stdscr, TRUE);
	
	while (1) {
		reset();
		score = 0;
		//Tresureの設定
		struct treasure place[5] = {
			{rand() % 27 + 1,rand() % 57 + 1},
			{rand() % 27 + 1,rand() % 57 + 1},
			{rand() % 27 + 1,rand() % 57 + 1},
			{rand() % 27 + 1,rand() % 57 + 1},
			{rand() % 27 + 1,rand() % 57 + 1},
		};
		struct treasure* tr;

		tr = place;

		for (i = 0; i < 5; i++) {
			field[(tr + i)->x_tresure][(tr + i)->y_tresure] = TREASURE;
		}

		//スタート画面
		while (1) {
			view_start();
			key = getch();
			if (key == 's') {
				break;
			}
		}
		
		//ゲーム画面
		while (1) {
			draw_field();
			attrset(COLOR_PAIR(1));
			mvaddstr(x, y, "@");
			attrset(COLOR_PAIR(3));
			mvprintw(15, 70, "FIND THE TREASURE!!");
			mvprintw(16, 70, "PRESS DIRECTION KEY→↑↓←!!");
			refresh();
			//キー操作
			key = getch();
			switch (key) {
			case KEY_RIGHT:
				if (y < 58) {
					field[x][y] = NULL_FIELD;
					y++;
				}
				break;
			case KEY_LEFT:
				if (1 < y) {
					field[x][y] = NULL_FIELD;
					y--;
				}
				break;
			case KEY_UP:
				if (1 < x) {
					field[x][y] = NULL_FIELD;
					x--;
				}
				break;
			case KEY_DOWN:
				if (x < 28) {
					field[x][y] = NULL_FIELD;
					x++;
				}
				break;
			}
			draw_field();
			//Treasureを見つけたら終了
			if (check_treasure(tr, x, y) == TRUE) {
				break;
			}
			refresh();
		}
		//画面の終了
		endwin();
		erase();
		//集計
		count_score();

		//結果画面
		while (1) {
			view_result();

			read_result(result);

			if (result[4] < score) {
				result[4] = score;
				for (int k = 4; k >= 0; k--) {
					if (result[k - 1] < result[k]) {
						int temp = result[k];
						result[k] = result[k - 1];
						result[k - 1] = temp;
					}

				}
			}

			//結果の表示
			getmaxyx(stdscr, h, w);
			for (int d = 0; d < NUMDATA; d++) {
				mvprintw(8 + d, w / 2 - 4, "%d位:%d", (d + 1), result[d]);
			}

			//ゲーム再スタート
			key = getch();
			if (key == 's') {
				erase();
				break;
			}

		}

		
		
	}


}



