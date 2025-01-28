#include "philo.h"

static int	check_philo_death(t_philo *philo)
{
	size_t	time_since_meal;

	pthread_mutex_lock(philo->meal);
	time_since_meal = get_live_time() - philo->time_last_meal;
	pthread_mutex_unlock(philo->meal);
	if (time_since_meal >= philo->info->time_to_die)
	{
		pthread_mutex_lock(philo->info->dead_check);
		philo->info->dead = 1;
		pthread_mutex_unlock(philo->info->dead_check);
		threaded_printf("died", philo);
		return (1);
	}
	return (0);
}

int	ft_life_check(t_philo *philos)
{
	int	i;

	i = -1;
	while (++i < philos->info->nb_of_philos)
	{
		if (philos[i].meal == NULL)
		{
			fprintf(stderr, "Meal mutex is NULL for philosopher %d\n", i);
			return (0);
		}
		pthread_mutex_lock(philos[i].meal);
		if (check_philo_death(&philos[i]))
		{
			pthread_mutex_unlock(philos[i].meal);
			return (0);
		}
		pthread_mutex_unlock(philos[i].meal);
	}
	return (1);
}

int	ft_nb_meals_done(t_philo *philos)
{
	int	i;
	int	full;

	full = 0;
	if (philos->info->nb_of_meals == -1)
		return (1);
	i = -1;
	while (++i < philos->info->nb_of_philos)
	{		
		pthread_mutex_lock(philos[i].meal);
        if (philos[i].meals_count >= philos->info->nb_of_meals)
            full++;
        pthread_mutex_unlock(philos[i].meal);
	}
	if (full == philos->info->nb_of_philos)
	{
		pthread_mutex_lock(philos->info->dead_check);
		philos->info->dead = 1;
		pthread_mutex_unlock(philos->info->dead_check);
		return (0);
	}
	return (1);
}

void	*ft_checker(void *arg)
{
	t_philo	*philos;

	philos = (t_philo *)arg;
	while (1)
	{
		if (ft_life_check(philos) == 0 || ft_nb_meals_done(philos) == 0)
			break ;
		usleep(100);
	}
	return (NULL);
}