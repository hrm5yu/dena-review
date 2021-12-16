#include "connect_four.h"

void	put_ball(int type)
{
	if (type == N)
		printf(".");
	else if (type == FIRST)
		printf("\x1b[31mo\x1b[39m");
	else if (type == SECOND)
		printf("\x1b[34mo\x1b[39m");
	else if (type == FOCUS)
		printf("\x1b[33mo\x1b[39m");
}

void	print_board(int	board[7][6], int turn)
{
	int	i;
	int	j;

	i = 0;
	printf("\033[2J");
	printf("---%s\x1b[39m PLAYER'S TURN---\n", turn == 1 ? "\x1b[31m1ST" : "\x1b[34m2ND");
	while (i < 7)
	{
		j = 0;
		printf("        ");
		while (j < 6)
		{
			put_ball(board[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

void	put_winner(int player)
{
	printf("----%s\x1b[39m PLAYER  WIN----\n", player == 2 ? "\x1b[31m1ST" : "\x1b[34m2ND");
}