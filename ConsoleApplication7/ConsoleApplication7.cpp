#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#define board_length 80
#define board_width 25
#define HALF_B_W 12
#define HALF_B_L 40

int Menu(int start);
void board();
void Move(int* move_rocket_l, int* move_rocket_r, int* exitp);
void Ball(int* move_rocket_l, int* move_rocket_r, int* Ball_Y_P, int* Ball_X_P, int* flag_P, int* vector_P, int* L_P_point_P, int* R_P_point_P);

int main() {
	int start = 0;
	if (Menu(start) == 2) {
		return 0;
	}
	else {
		fseek(stdin, 0, SEEK_END);
		board();
	}
}

int Menu(int start) {
	printf("\n\n\n%55cMenu\n\n", ' ');
	printf("\n%50cPress 1 to start\n", ' ');
	printf("\n%50cPress 2 to exit\n", ' ');
	while (scanf("%d", &start) != 1 || (start != 1 && start != 2)) {
		printf("incorrect\n");
		fseek(stdin, 0, SEEK_END);
	}
	return start;
}

void board() {
	srand(time(NULL));
	int rocketl = 0;
	int rocketr = 0;
	int Ball_Y = 0;
	int Ball_X = 0;
	int flag = rand() % 2;
	int vector = rand() % 2;
	int L_P_point = 0;
	int R_P_point = 0;
	int exit = 0;
	int* exitp = &exit;
	int* L_P_point_P = &L_P_point;
	int* R_P_point_P = &R_P_point;
	int* move_rocket_l = &rocketl;
	int* move_rocket_r = &rocketr;
	int* Ball_Y_P = &Ball_Y;
	int* Ball_X_P = &Ball_X;
	int* flag_P = &flag;
	int* vector_P = &vector;
	char board[board_width][board_length];
	while ((L_P_point != 10 && R_P_point != 10) && exit != 1) {
		system("cls");
		printf("LR%d RR%d BX%d BY%d %d\n", rocketl, rocketr, Ball_X, Ball_Y, exit);
		printf("\t PLAYER ONE- %d", L_P_point);
		printf("\t\t\t\t\t PLAYER TWO- %d\n", R_P_point);
		for (int i = 0; i < board_width; i++) {
			for (int j = 0; j < board_length; j++) {
				if ((i == 0 || i == board_width - 1) && j > 0 && j < board_length - 1) {
					board[i][j] = '-';
				}
				else if ((i == 0 || i > 0) && (j == 0 || j == board_length - 1)) {
					board[i][j] = '|';
				}
				else {
					board[i][j] = ' ';
				}
			}
		}
		for (int i = 0; i < board_width; i++) {
			for (int j = 0; j < board_length; j++) {
				if ((i >= 11 + *move_rocket_l && i <= 13 + *move_rocket_l) && j == 4) {
					board[i][j] = '|';
				}
				else if ((i >= 11 + *move_rocket_r && i <= 13 + *move_rocket_r) && j == 75) {
					board[i][j] = '|';
				}
			}
		}
		for (int i = 0; i < board_width; i++) {
			for (int j = 0; j < board_length; j++) {
				if (i == HALF_B_W + Ball_Y && j == HALF_B_L + Ball_X) {
						board[i][j] = 'O';
				}
			}
		}
		for (int i = 0; i < board_width; i++) {
			for (int j = 0; j < board_length; j++) {
				if (j == board_length - 1) {
					printf("%c\n", board[i][j]);
				}
				else {
					printf("%c", board[i][j]);
				}
			}
		}
		Move(move_rocket_l, move_rocket_r, exitp);
		Ball(move_rocket_l, move_rocket_r, Ball_Y_P, Ball_X_P, flag_P, vector_P, L_P_point_P, R_P_point_P);
		Sleep(50);
	}
	system("cls");
	if (L_P_point == 10) {
		printf("\n\n%50cPLAYER ONE WIN!", ' ');
	} else if (R_P_point == 10) {
		printf("\n\n%50cPLAYER TWO WIN!", ' ');
	} else {
		printf("\n\n%50cSEE YOU SOON", ' ');
	}
	getchar();
}

void Move(int* move_rocket_l, int* move_rocket_r, int* exitp) {
	if (_kbhit()) {
		switch (_getch()) {
		case 'a':
			if (*move_rocket_l > -10) {
				*move_rocket_l -= 1;
				break;
			} else break;
		case 'z':
			if (*move_rocket_l < 10) {
				*move_rocket_l += 1;
				break;
			} else break;
		case 'k':
			if (*move_rocket_r > -10) {
				*move_rocket_r -= 1;
				break;
			} else break;
		case 'm':
			if (*move_rocket_r < 10) {
				*move_rocket_r += 1;
				break;
			} else break;
		case 27:
			*exitp = 1;
			break;
		}
	}
}

void Ball(int* move_rocket_l, int* move_rocket_r, int* Ball_Y_P, int* Ball_X_P, int* flag_P, int* vector_P, int* L_P_point_P, int* R_P_point_P) {
	if ((HALF_B_W + *Ball_Y_P) == board_width - 2) {
		if ((* move_rocket_l == 10 || *move_rocket_l == 9) && HALF_B_L + *Ball_X_P == 5) {
			*flag_P = 1;
			*vector_P = 0;
		} else if ((*move_rocket_r == 10 || *move_rocket_r == 9) && HALF_B_L + *Ball_X_P == 74) {
			*flag_P = 1;
			*vector_P = 1;
		} else{
			*flag_P = 1;
		}
	} else if (HALF_B_L + *Ball_X_P == board_length - 2) {
		*flag_P = 2;
	} else if (HALF_B_W + *Ball_Y_P == 1) {
		if ((* move_rocket_l == -10 || *move_rocket_l == -9) && HALF_B_L + *Ball_X_P == 5) {
			*flag_P = 0;
			*vector_P = 0;
		} else if ((*move_rocket_r == -10 || *move_rocket_r == -9) && HALF_B_L + *Ball_X_P == 74) {
			*flag_P = 0;
			*vector_P = 1;
		} else{
			*flag_P = 0;
		}
	} else if (HALF_B_L + *Ball_X_P == 1) {
		*flag_P = 3;
	} else if ((HALF_B_L + *Ball_X_P == 74) && (HALF_B_W + *Ball_Y_P >= 10 + *move_rocket_r && HALF_B_W + *Ball_Y_P <= 14 + *move_rocket_r)) {
		*vector_P = 1;
	} else if ((HALF_B_L + *Ball_X_P == 5) && (HALF_B_W + *Ball_Y_P >= 10 + *move_rocket_l && HALF_B_W + *Ball_Y_P <= 14 + *move_rocket_l)) {
		*vector_P = 0;
	}

	if (*flag_P == 0 && *vector_P == 0) {
		*Ball_Y_P += 1;
		*Ball_X_P += 1;
	} else if (*flag_P == 1 && *vector_P == 0) {
		*Ball_Y_P -= 1;
		*Ball_X_P += 1;
	} else if (*flag_P == 0 && *vector_P == 1) {
		*Ball_Y_P += 1;
		*Ball_X_P -= 1;
	} else if (*flag_P == 1 && *vector_P == 1) {
		*Ball_Y_P -= 1;
		*Ball_X_P -= 1;
	} else if (*flag_P == 2) {
		*Ball_Y_P = 0;
		*Ball_X_P = 0;
		*flag_P = rand() % 2;
		*vector_P = rand() % 2;
		*move_rocket_l = 0;
		*move_rocket_r = 0;
		*L_P_point_P += 1;
	} else if (*flag_P == 3) {
		*Ball_Y_P = 0;
		*Ball_X_P = 0;
		*flag_P = rand() % 2;
		*vector_P = rand() % 2;
		*move_rocket_l = 0;
		*move_rocket_r = 0;
		*R_P_point_P += 1;
	}
}
