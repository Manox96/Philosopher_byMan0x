#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <limits.h>


typedef struct s_philo
{
	int					id_philo;
	int					left_fork;
	int					right_fork;


	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
	int				all_philos_eat;
	int				a_philo_dead;
	long			starting_Time;
	pthread_mutex_t	*forks;
	pthread_mutex_t		all_eat;
	pthread_mutex_t		what_he_do;
	pthread_mutex_t		death;
	pthread_mutex_t		eaten_times;

}	t_data;



int	my_atoi(char *str);
void initial_data(t_data *data,int ac,char **av);
void	print_err(char *str);
int	ft_isdigit(int c);
void createPhilo(t_data *data);
#endif