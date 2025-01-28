#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>
# include <pthread.h>
# include <string.h>
# include <limits.h>
# include <sys/time.h>
# include <stdatomic.h>
typedef struct s_box t_box;

typedef struct s_philo
{
	int				index;
	int		eating;
	size_t	time;
	size_t	time_last_meal;
	int		meals_count;
	pthread_t		thread;
	pthread_mutex_t	*fork;
	pthread_mutex_t	*meal;
	t_box			*info;
}	t_philo;

struct s_box
{
	pthread_mutex_t	*msg;
	pthread_mutex_t	*dead_check;
	int		dead;
	int		stoop;
	int				nb_of_philos;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				nb_of_meals;
	t_philo *philos;
};


void	ft_set_all(t_philo *philo, t_box *box);
int		ft_check_input(int ac, char **av);
int		main(int ac, char **av);
void	ft_putstr_fd(char *s, int fd);
long	ft_atoi(char *str);
size_t	get_live_time(void);
int		ft_usleep(t_philo *philos, size_t milliseconds);
void	*ft_routing(void *arg);
void	*ft_checker(void *arg);
void	threaded_printf(char *str, t_philo *philo);
int		ft_set_mutex(t_philo *philos, t_box *box);



#endif
