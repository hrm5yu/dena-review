NAME = connect_four
CC = GCC
CFLAGS = -Wall -Wextra -Werror
SRCS = print.c main.c judge.c control.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm  $(OBJS)

fclean: clean
	rm  $(NAME)

re: fclean all

.PHONY: all clean fclean re

