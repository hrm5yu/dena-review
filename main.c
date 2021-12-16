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