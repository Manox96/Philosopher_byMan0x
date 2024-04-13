SRCS = 	philosopher.c \
			utils_philo.c \

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

.PHONY: clean