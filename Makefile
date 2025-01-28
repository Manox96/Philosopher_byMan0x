

NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror 
RM = rm -f

SRCS = main.c ft_utils.c  ft_routing.c ft_checker.c ft_thread_util.c \


OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
		$(CC) $(OBJS) -o $(NAME)

philo/%.o : philo/%.c philo/philo.h
		$(CC) $(CFLAGS) -c $< -o $@

clean:
		$(RM) $(OBJS)

fclean: clean
		$(RM) $(NAME)

re: fclean all

.PHONY: clean fclean
