#include "connect_four.h"

int	connect_count(t_game *game, int x, int y, int flag)
{
	if (y < 0 || y > 6 || x < 0 || x > 5 || game->board[y][x] != game->turn)
		return (0);
	if (flag == DIAGONAL)
		return (1 + connect_count(game, x + 1, y + 1, flag));
	if (flag == R_DIAGONAL)
		return (1 + connect_count(game, x + 1, y - 1, flag));
	if (flag == HORIZON)
		return (1 + connect_count(game, x + 1, y, flag));
	if (flag == VERTICAL)
		return (1 + connect_count(game, x, y + 1, flag));
	return (0);
}

int	diagonal(t_game *game, int y)
{
	int x;

	x = game->posx;
	while (y > 0 && x > 0 && game->board[y - 1][x - 1] == game->turn)
	{
		y--;
		x--;
	}
	if (connect_count(game, x, y, DIAGONAL) >= 4)
		return (1);
	return (0);
}

int	r_diagonal(t_game *game, int y)
{
	int x;

	x = game->posx;
	while (y < 6 && x > 0 && game->board[y + 1][x - 1] == game->turn)
	{
		y++;
		x--;
	}
	if (connect_count(game, x, y, R_DIAGONAL) >= 4)
		return (1);
	return (0);
}

int	horizon(t_game *game, int y)
{
	int x;

	x = game->posx;
	while (x > 0 && game->board[y][x - 1] == game->turn)
		x--;
	if (connect_count(game, x, y, HORIZON) >= 4)
		return (1);
	return (0);
}

int	vertical(t_game *game, int y)
{
	while (y > 0 && game->board[y - 1][game->posx] == game->turn)
		y--;
	if (connect_count(game, game->posx, y, VERTICAL) >= 4)
		return (1);
	return (0);
}

void	judge(t_game *game)
{
	int	i;

	i = 0;
	while (game->board[i][game->posx] == 0 || game->board[i][game->posx] == 3)
		i++;
	if (diagonal(game, i) || r_diagonal(game, i) || horizon(game, i) || vertical(game, i))
	{
		print_board(game->board, game->turn);
		printf("---WINEER %s\x1b[39m PLAYER---\n", game->turn == 1 ? "\x1b[31m1ST" : "\x1b[34m2ND");
		exit(1);
	}
	if (game->turn == 2)
		game->turn = 1;
	else
		game->turn = 2;
}