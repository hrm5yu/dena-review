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
	int	j;

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