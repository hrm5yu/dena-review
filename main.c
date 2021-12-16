#include "connect_four.h"

void	init_game(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < 7)
	{
		j = 0;
		while (j < 6)
		{
			game->board[i][j] = 0;
			if (i == 6 && j == 0)
				game->board[i][j]= 3;
			j++;
		}
		i++;
	}
	game->finish = 0;
	game->posx = 0;
	game->turn = 1;
}


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

int main()
{
	struct termios termios;
	t_game game;
	int	c;

	tcgetattr(STDIN_FILENO, &termios);
    termios.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &termios);
	init_game(&game);
	print_board(game.board, game.turn);
	while (!game.finish)
	{
		c = getchar();
		board_controller(c, &game);
		print_board(game.board, game.turn);
	}
}