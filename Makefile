NAME = philo

SRCS = init.c\
		main.c\
		monitor.c\
		run.c\
		util.c
		
OBJS = $(SRCS:.c=.o)
CC = gcc
RM = rm -f
CFLAGS = -g -Wall -Wextra -Werror -I.

all: $(NAME)

$(NAME): $(OBJS)
			$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
			$(RM) $(OBJS)

fclean: clean
			$(RM) $(NAME)

re: 	fclean $(NAME)

.PHONY:		all clean fclean re

