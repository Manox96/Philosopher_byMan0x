#include "philo.h"

size_t	get_live_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
	{
		write(2, "gettimeofday() error\n", 22);
		return 0;
	}
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_usleep(t_philo *philos, size_t milliseconds)
{
	size_t	start;

	start = get_live_time();
	if (philos->info->dead == 0)
	{
		while ((get_live_time() - start) < milliseconds)
			usleep(500);
	}
	return (0);
}

void	threaded_printf(char *str, t_philo *philo)
{
	size_t	time;

	pthread_mutex_lock(philo->info->msg);
	pthread_mutex_lock(philo->info->dead_check);
	time = get_live_time();
	if (philo->info->dead == 0)
		printf("%zu  %d  %s\n", time - philo->time, philo->index, str);
	pthread_mutex_unlock(philo->info->dead_check);
	pthread_mutex_unlock(philo->info->msg);
}
