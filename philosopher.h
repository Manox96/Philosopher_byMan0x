#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <limits.h>
# include <sys/time.h>
# include <errno.h>

typedef struct s_data t_data;
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
	pthread_t			thread_id;
	int						last_time_eat;
	int						is_fulll;
	int						meals_c;
	struct s_data			*data;
}	t_philo;

typedef enum e_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_LEFT_FORK,
	TAKE_RIGHT_FORK,
	DEAD,
}	t_status;

typedef enum e_type
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
} t_type;

typedef enum e_time
{
	SECOND,
	MILLISECOND,
	MICROSECOND,

} t_time;


struct s_data
{
	int				nbrs_philo;
	int				must_eat;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				limit_eat;
	int				start_sum;
	int				end_sum;
	int				all_ready;
	pthread_mutex_t	dt_mutex;
	t_philo				*philo;
	t_fork				*fork;
};



long long	get_time(t_time time_MOS);
void philo_init(t_data *data);
void	free_all(t_data *dt);
void handle_mtx_err(int status, t_type type);
void	handle_mutex(t_type type, pthread_mutex_t *mtx);
int	my_atoi(char *str);
void initial_inputs(t_data *data,int ac,char **av);
void	print_err(char *str);
void handle_thread_err(int status, t_type type);
void	handle_thread(pthread_t *thread, void *(*foo)(void *), void *data, t_type type);
void start_sumilation(t_data *data);
int	ft_isdigit(int c);
void createProps(t_data *data);
void	*ft_malloc(size_t size);
void intial_data(t_data *data);
void	handle_mutex(t_type type, pthread_mutex_t *mtx);
void	*ft_malloc(size_t size);
void handle_mtx_err(int status, t_type type);

long long	satrted_time(void);
#endif