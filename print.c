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

void	drop_ball(t_game *game)
{
	int	i;

	i = 0;
	if (game->board[0][game->posx] != 0 && game->board[0][game->posx] != 3)
		return ;
	while (i < 6 && (game->board[i + 1][game->posx] == 0 || game->board[i + 1][game->posx] == 3))
	{
		game->board[i][game->posx] = game->turn;
		print_board(game->board, game->turn);
		game->board[i][game->posx] = 0;
		usleep(100000);
		i++;
	}
	game->board[i][game->posx] = game->turn;
	if (i - 1 >= 0)
		game->board[i - 1][game->posx] = FOCUS;
}

int	search_focus(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < 7)
	{
		j = 0;
		while (j < 6)
		{
			if (game->board[i][j] == 3)
				return (j);
			j++;
		}
		i++;
	}
	return (-1);
}

void focus_ball(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	j = search_focus(game);
	while (j != -1 && i < 6 && (game->board[i][j] != 3))
		i++;
	if (j != -1)
		game->board[i][j] = 0;
	i = 0;
	while (i < 6 && game->board[i + 1][game->posx] == 0)
		i++;
	if (game->board[i][game->posx] == 0)
		game->board[i][game->posx] = 3;
}