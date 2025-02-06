NAME = pipex
CC = gcc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I includes
RM = rm -f

SRCS =	sources/main.c \
		sources/utils.c \
		sources/childs.c \
		sources/split.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re