SRCS = 	philosopher.c \
			utils_philo.c \
			parsing.c \
			utils_philosTwo.c \

CC = cc
CFLAGS = -Wall -Werror -Wextra -pthread
RM = rm -rf
OBJS = $(SRCS:.c=.o)
NAME = philo
H_MOND = philo.h

%.o: %.c $(H_MOND)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all
	$(RM) $(OBJS) && clear

go :
	make && make clean && clear
.PHONY: clean