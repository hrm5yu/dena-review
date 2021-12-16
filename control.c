#include "connect_four.h"


void	right_shift(t_game *game)
{
	int	i;

	i = game->posx;
	if (i < 5 && game->board[0][i + 1] == 0)
		i++;
	else
		while (i < 5 && game->board[0][++i] != 0)
			;
	if (game->board[0][i] == 0)
		game->posx = i;
	focus_ball(game);
}

void	left_shift(t_game *game)
{
	int	i;

	i = game->posx;
	if (i > 0 && game->board[0][i - 1] == 0)
		i--;
	else
		while (i > 0 && game->board[0][--i] != 0)
			;
	if (game->board[0][i] == 0)
		game->posx = i;
	focus_ball(game);
}

void	board_controller(int c, t_game *game)
{
	int i;

	i = 0;
	while (game->board[0][i] != 0 && game->board[0][i] != 3 && i < 6)
		i++;
	if (i == 6)
		exit(1);
	if (c == 'd')
		right_shift(game);
	else if (c == 'a')
		left_shift(game);
	else if (c == ' ')
	{
		drop_ball(game);
		judge(game);
	}
	else if (c == 'q')
		exit(1);
}