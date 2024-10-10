#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <limits.h>
# include <sys/time.h>
# include <errno.h>


typedef struct s_fork
{
	int				fork_id;
	pthread_mutex_t fork;
}	t_fork;

typedef struct s_philo
{
	int						id_philo;
	t_fork					*left_fork;
	t_fork					*right_fork;
	int						last_time_eat;
	int						is_fulll;
	int						meals_c;
	struct s_data			*data;
}	t_philo;

typedef enum e_type
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CRERATE,
	JOIN,
	DETACH,
} t_type;



typedef struct s_data
{
	int				nbrs_philo;
	int				must_eat;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				limit_eat;
	int				start_sum;
	int				end_sum;
	t_philo				*philo;
	t_fork				*fork;
}	t_data;



void handle_mtx_err(int status, t_type type);
void	handle_mutex(t_type type, pthread_mutex_t *mtx);
int	my_atoi(char *str);
void initial_inputs(t_data *data,int ac,char **av);
void	print_err(char *str);
int	ft_isdigit(int c);
void createProps(t_data *data);
void	*ft_malloc(size_t size);
void intial_data(t_data *data);
void	handle_mutex(t_type type, pthread_mutex_t *mtx);
void	*ft_malloc(size_t size);
void handle_mtx_err(int status, t_type type);

long long	satrted_time(void);
#endif