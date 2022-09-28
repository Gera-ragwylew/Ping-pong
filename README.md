# ConsoleApplication7
// Online C compiler to run C program online
#include <stdio.h>
#define board_length 80
#define board_width 25
#define HALF_B_W 12
#define HALF_B_L 40

int Move(int flag);

int main() {
    int X = 0;
    int Y = 0;
    int Si = 12;
    int Sj = 41;
    int Si2 = 12;
    int Sj2 = 42;
    int flag = 0;
    char board[board_width][board_length];
    while (1) {
        for (int i = 0; i < board_width; i++) {
		    for (int j = 0; j < board_length; j++) {
			    if ((i == 0 || i == board_width - 1) && j > 0 && j < board_length - 1) {
			    	board[i][j] = '-';
			    } else if ((i == 0 || i > 0) && (j == 0 || j == board_length - 1)) {
				    board[i][j] = '|';
			    }else {
				    board[i][j] = ' ';
			    }
		    }
	    }
	    for (int i = 0; i < board_width; i++) {
		    for (int j = 0; j < board_length; j++) {
			    if (i == Si2 && j == Sj2) {
				    board[i][j] = 'O';
			    }
		    }
	    }
	    for (int i = 0; i < board_width; i++) {
		    for (int j = 0; j < board_length; j++) {
			    if (i == Si && j == Sj) {
				    board[i][j] = 'O';
				    Sj2 = j;
				    Si2 = i;
			    }
		    }
	    }
	    for (int i = 0; i < board_width; i++) {
		    for (int j = 0; j < board_length; j++) {
			    if (i == HALF_B_W + Y && j == HALF_B_L + X) {
				    board[i][j] = 'S';
				    Si = i;
				    Sj = j;
			    }
		    }
	    }
    	for (int i = 0; i < board_width; i++) {
		    for (int j = 0; j < board_length; j++) {
			    if (j == board_length - 1) {
				    printf("%c\n", board[i][j]);
			    }else {
				    printf("%c", board[i][j]);
			    }
		    }
	    }
	    flag = Move(flag);
	    if (flag == 0) {
	        X--;
	    } else if (flag == 1) {
	        Y--;
	    } else if (flag == 2) {
	        Y++;
	    } else if (flag == 3) {
	        X++;
	    }
    }
    
}

int Move(int flag) {
	char c;
	scanf("%c", &c);
	if (c == 'w') {
		flag = 1;
	} else if (c == 's') {
		flag = 2;
	} else if (c == 'a') {
		flag = 0;
	} else if (c == 'd') {
		flag = 3;
	}
	fseek(stdin, 0, SEEK_END);
	return flag;
}
