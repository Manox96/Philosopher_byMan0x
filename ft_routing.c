#include "philo.h"

void	think(t_philo *philo)
{
	threaded_printf("is thinking", philo);
}

void	sleep_philo(t_philo *philo)
{
	threaded_printf("is sleeping", philo);
	ft_usleep(philo, philo->info->time_to_sleep);
}

static int	take_first_fork(t_philo *philo)
{
	if (pthread_mutex_lock(philo->fork) != 0)
	{
		fprintf(stderr, "Failed to lock fork for philosopher %d\n", philo->index);
		return (0);
	}
	threaded_printf("has taken a fork", philo);
	return (1);
}

static int	take_second_fork(t_philo *philo, int next_idx)
{
	if (pthread_mutex_lock(philo->info->philos[next_idx].fork) != 0)
	{
		pthread_mutex_unlock(philo->fork);
		fprintf(stderr, "Failed to lock next fork for philosopher %d\n",
			philo->index);
		return (0);
	}
	threaded_printf("has taken a fork", philo);
	return (1);
}

static void	update_meal_time(t_philo *philo)
{
	pthread_mutex_lock(philo->meal);
	philo->eating = 1;
	philo->time_last_meal = get_live_time();
	pthread_mutex_unlock(philo->meal);
}

// static void	handle_single_philo(t_philo *philo)
// {
// 	pthread_mutex_unlock(philo->fork);
// 	ft_usleep(philo, philo->info->time_to_die);
// }

void	eat(t_philo *philo)
{
	int	next_index;

	next_index = (philo->index + 1) % philo->info->nb_of_philos;

	// Check if forks are available
	if (!philo->fork || !philo->info->philos[next_index].fork)
	{
		fprintf(stderr, "Invalid fork mutex for philosopher %d\n", philo->index);
		return;
	}

	// Lock the lower-numbered fork first to prevent deadlock
	if (philo->index < next_index)
	{
		if (!take_first_fork(philo))
			return;
		if (!take_second_fork(philo, next_index))
			return;
	}
	else
	{
		if (!take_second_fork(philo, next_index))
			return;
		if (!take_first_fork(philo))
			return;
	}

	// Update meal time and eating status
	update_meal_time(philo);
	threaded_printf("is eating", philo);
	ft_usleep(philo, philo->info->time_to_eat);

	// Release forks
	pthread_mutex_unlock(philo->fork);
	pthread_mutex_unlock(philo->info->philos[next_index].fork);
}

int	check_stop(t_philo *philo)
{
	pthread_mutex_lock(philo->info->dead_check);
	if (philo->info->dead == 1)
	{
		pthread_mutex_unlock(philo->info->dead_check);
		return (0);
	}
	pthread_mutex_unlock(philo->info->dead_check);
	return (1);
}

void	*ft_routing(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->index % 2 == 0)
        ft_usleep(philo, philo->info->time_to_eat / 2);

	while (check_stop(philo))
	{
		eat(philo);
		sleep_philo(philo);
		think(philo);
	}
	return (arg);
}