#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <termios.h>
#include <fcntl.h>

#define N 0
#define FIRST 1
#define SECOND 2
#define FOCUS 3
#define DIAGONAL 1
#define R_DIAGONAL 2
#define HORIZON 3
#define VERTICAL 4

typedef struct s_game
{
	int board[7][6];
	int	posx;
	int	turn;
	int	finish;
}			t_game;

void	put_ball(int type);
void	print_board(int	board[][6], int turn);
int		kbhit(void);
void	put_winner(int player);