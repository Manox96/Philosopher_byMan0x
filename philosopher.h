#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>

typedef struct s_philo
{
	pthread_t	th;
	int	philo_num;
	int	time_to_eat_num;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;

} t_philo;

typedef struct s_table
{

} t_table;



int checkOnly_num(char **av);
int	my_atoi(char *str);
#endif