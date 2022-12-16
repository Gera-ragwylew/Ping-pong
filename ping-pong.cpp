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

int Menu(int exit);
void Move(int* move_rocket_l, int* move_rocket_r, int* exitp);
void Ball(int* move_rocket_l, int* move_rocket_r, int* Ball_Y_P, int* Ball_X_P, int* flag_P, int* vector_P, int* L_P_point_P, int* R_P_point_P);
void End(int L_P_point, int R_P_point);

int main() {
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

	srand(time(NULL));
	exit = Menu(exit); // начальное меню
	while ((L_P_point != 10 && R_P_point != 10) && exit != 2) { // основной цикл игры
		system("cls"); // очистка экрана
		printf("LR%d RR%d BX%d BY%d %d\n", rocketl, rocketr, Ball_X, Ball_Y, exit);
		printf("\t PLAYER ONE- %d", L_P_point);
		printf("\t\t\t\t\t PLAYER TWO- %d\n", R_P_point);
		for (int i = 0; i < board_width; i++) { // заполнение массива полем
			for (int j = 0; j < board_length; j++) {
				if ((i == 0 || i == board_width - 1) && j > 0 && j < board_length - 1) {
					board[i][j] = '-';
				} else if ((i == 0 || i > 0) && (j == 0 || j == board_length - 1)) {
					board[i][j] = '|';
				} else {
					board[i][j] = ' ';
				}
			}
		}
		for (int i = 0; i < board_width; i++) { // добавление в массив ракеток
			for (int j = 0; j < board_length; j++) {
				if ((i >= 11 + *move_rocket_l && i <= 13 + *move_rocket_l) && j == 4) {
					board[i][j] = '|';
				} else if ((i >= 11 + *move_rocket_r && i <= 13 + *move_rocket_r) && j == 75) {
					board[i][j] = '|';
				}
			}
		}
		for (int i = 0; i < board_width; i++) { // добавление в массив шарика
			for (int j = 0; j < board_length; j++) {
				if (i == HALF_B_W + Ball_Y && j == HALF_B_L + Ball_X) {
					board[i][j] = 'O';
				}
			}
		}
		for (int i = 0; i < board_width; i++) { // отрисовка массива
			for (int j = 0; j < board_length; j++) {
				if (j == board_length - 1) {
					printf("%c\n", board[i][j]);
				} else {
					printf("%c", board[i][j]);
				}
			}
		}
		Move(move_rocket_l, move_rocket_r, exitp); // ф-ия нажатия клавиш и движения ракеток
		Ball(move_rocket_l, move_rocket_r, Ball_Y_P, Ball_X_P, flag_P, vector_P, L_P_point_P, R_P_point_P); // ф-ия физики шарика
		Sleep(50); // скорость отрисовки (длительность паузы)
	}
	End(L_P_point, R_P_point); // ф-ия завершения игры
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
			*exitp = 2;
			break;
		}
	}
}

void Ball(int* move_rocket_l, int* move_rocket_r, int* Ball_Y_P, int* Ball_X_P, int* flag_P, int* vector_P, int* L_P_point_P, int* R_P_point_P) {
	// исправление бага прохождения шарика сквозь ракетку при ударе в угол
	if ((HALF_B_W + *Ball_Y_P) == board_width - 2) { 
		if ((*move_rocket_l == 10 || *move_rocket_l == 9) && HALF_B_L + *Ball_X_P == 5) { // левый нижний угол (исправление)
			*flag_P = 1;
			*vector_P = 0;
		} else if ((*move_rocket_r == 10 || *move_rocket_r == 9) && HALF_B_L + *Ball_X_P == 74) { // правый нижний угол (исправление)
			*flag_P = 1;
			*vector_P = 1;
		} else{ // удар о нижнюю границу поля (основа)
			*flag_P = 1;
		}
	} else if (HALF_B_W + *Ball_Y_P == 1) {
		if ((*move_rocket_l == -10 || *move_rocket_l == -9) && HALF_B_L + *Ball_X_P == 5) { // левый верхний угол (исправление)
			*flag_P = 0;
			*vector_P = 0;
		} else if ((*move_rocket_r == -10 || *move_rocket_r == -9) && HALF_B_L + *Ball_X_P == 74) { // правый верхний угол (исправление)
			*flag_P = 0;
			*vector_P = 1;
		} else{ // удар о верхнюю границу поля (основа)
			*flag_P = 0;
		}
	// основа физики шарика
	} else if (HALF_B_L + *Ball_X_P == board_length - 2) { // шарик пересекает правую стенку
		*flag_P = 2;
	} else if (HALF_B_L + *Ball_X_P == 1) { // шарик пересекает левую стенку
		*flag_P = 3;
	} else if ((HALF_B_L + *Ball_X_P == 74) && (HALF_B_W + *Ball_Y_P >= 10 + *move_rocket_r && HALF_B_W + *Ball_Y_P <= 14 + *move_rocket_r)) { // удар в правую ракетку
		*vector_P = 1; 
	} else if ((HALF_B_L + *Ball_X_P == 5) && (HALF_B_W + *Ball_Y_P >= 10 + *move_rocket_l && HALF_B_W + *Ball_Y_P <= 14 + *move_rocket_l)) { // удар в левую ракетку
		*vector_P = 0;
	}
	// изменение траектории движения
	if (*flag_P == 0 && *vector_P == 0) { // движение вправо вниз
		*Ball_Y_P += 1;
		*Ball_X_P += 1;
	} else if (*flag_P == 1 && *vector_P == 0) { // движение вправо вверх
		*Ball_Y_P -= 1;
		*Ball_X_P += 1;
	} else if (*flag_P == 0 && *vector_P == 1) { // движение влево вниз
		*Ball_Y_P += 1;
		*Ball_X_P -= 1;
	} else if (*flag_P == 1 && *vector_P == 1) { // движение влево вверх
		*Ball_Y_P -= 1;
		*Ball_X_P -= 1;
	} else if (*flag_P == 2) { // гол правому(2) игроку
		*Ball_Y_P = 0;
		*Ball_X_P = 0;
		*flag_P = rand() % 2;
		*vector_P = rand() % 2;
		*move_rocket_l = 0;
		*move_rocket_r = 0;
		*L_P_point_P += 1;
	} else if (*flag_P == 3) { // гол игроку(1) игроку
		*Ball_Y_P = 0;
		*Ball_X_P = 0;
		*flag_P = rand() % 2;
		*vector_P = rand() % 2;
		*move_rocket_l = 0;
		*move_rocket_r = 0;
		*R_P_point_P += 1;
	}
}

int Menu(int exit) {
	printf("\n\n\n%55cMenu\n\n", ' ');
	printf("\n%50cPress 1 to start\n", ' ');
	printf("\n%50cPress 2 to exit\n", ' ');
	while (scanf("%d", &exit) != 1 || (exit != 1 && exit != 2)) {
		printf("incorrect\n");
		fseek(stdin, 0, SEEK_END); // очистка потока STDIN (чтобы не зациклить вариант с буквой)
	}
	return exit;
}

void End(int L_P_point, int R_P_point) {
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
