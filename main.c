#include "philo.h"
#include <stdlib.h>

static int	check_args_values(int ac, char **av)
{
	int	i;
	int	value;

	i = 1;
	while (i < ac)
	{
		value = ft_atoi(av[i]);
		if (value <= 0 || value > 2147483647)
			return (ft_putstr_fd("Invalid argument value\n", 2), 0);
		if (i == 1 && value > 200)
			return (ft_putstr_fd("Number of philosophers cannot exceed 200\n", 2), 0);
		if (i > 1 && i < 5 && value < 60)
			return (ft_putstr_fd("Time values must be at least 60ms\n", 2), 0);
		i++;
	}
	return (1);
}

int	ft_check_input(int ac, char **av)
{
	if (ac != 5 && ac != 6)
	{
		ft_putstr_fd("Usage: ./philo <nb_of_philos> <time_to_die> "
		"<time_to_eat> <time_to_sleep> [nb_of_meals]\n", 2);
		return (0);
	}
	return (check_args_values(ac, av));
}

static int	init_mutexes(t_box *box)
{
	box->msg = malloc(sizeof(pthread_mutex_t));
	box->dead_check = malloc(sizeof(pthread_mutex_t));
	if (!box->msg || !box->dead_check)
	{
		ft_putstr_fd("Memory allocation failed\n", 2);
		return (0);
	}
	if (pthread_mutex_init(box->msg, NULL) != 0)
		return (0);
	if (pthread_mutex_init(box->dead_check, NULL) != 0)
	{
		pthread_mutex_destroy(box->msg);
		return (0);
	}
	return (1);
}

int	ft_fill_box(int ac, char **av, t_box *box)
{
	if (!init_mutexes(box))
	{
		free(box->msg);
		free(box->dead_check);
		return (0);
	}
	box->nb_of_philos = ft_atoi(av[1]);
	box->time_to_die = ft_atoi(av[2]);
	box->time_to_eat = ft_atoi(av[3]);
	box->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		box->nb_of_meals = ft_atoi(av[5]);
	else
		box->nb_of_meals = -1;
	return (1);
}

static int	init_philo_mutex(t_philo *philo)
{
	philo->fork = malloc(sizeof(pthread_mutex_t));
	philo->meal = malloc(sizeof(pthread_mutex_t));
	if (!philo->fork || !philo->meal)
		return (0);
	if (pthread_mutex_init(philo->fork, NULL) != 0)
		return (0);
	if (pthread_mutex_init(philo->meal, NULL) != 0)
	{
		pthread_mutex_destroy(philo->fork);
		return (0);
	}
	return (1);
}

static void	cleanup_mutexes(t_philo *philos, int limit)
{
	int	i;

	i = -1;
	while (++i < limit)
	{
		pthread_mutex_destroy(philos[i].fork);
		free(philos[i].fork);
		pthread_mutex_destroy(philos[i].meal);
		free(philos[i].meal);
	}
}

int	ft_set_mutex(t_philo *philos, t_box *box)
{
	int	i;

	i = -1;
	while (++i < box->nb_of_philos)
	{
		if (!init_philo_mutex(&philos[i]))
		{
			cleanup_mutexes(philos, i);
			return (0);
		}
	}
	return (1);
}

static int	create_philo_threads(t_philo *philos, t_box *box)
{
	int			i;
	pthread_t	checker;

	i = -1;
	if (pthread_create(&checker, NULL, &ft_checker, philos) != 0)
		return (0);
	while (++i < box->nb_of_philos)
	{
		if (pthread_create(&philos[i].thread, NULL, &ft_routing, &philos[i]) != 0)
		{
			ft_putstr_fd("Thread creation failed\n", 2);
			exit(EXIT_FAILURE);
		}
	}
	if (pthread_join(checker, NULL) != 0)
		return (0);
	return (1);
}

static int	join_philo_threads(t_philo *philos, t_box *box)
{
	int	i;

	i = -1;
	while (++i < box->nb_of_philos)
	{
		if (pthread_join(philos[i].thread, NULL) != 0)
			return (0);
	}
	return (1);
}

void	ft_threading(t_philo *philos, t_box *box)
{
	if (!philos || !box)
		exit(EXIT_FAILURE);
	if (!create_philo_threads(philos, box))
		exit(EXIT_FAILURE);
	if (!join_philo_threads(philos, box))
		exit(EXIT_FAILURE);
}

void	ft_cleanup(t_philo *philos, t_box *box)
{
	int	i;

	i = -1;
	pthread_mutex_destroy(box->msg);
	pthread_mutex_destroy(box->dead_check);
	free(box->msg);
	free(box->dead_check);
	while (++i < box->nb_of_philos)
	{
		if (philos[i].fork)
		{
			pthread_mutex_destroy(philos[i].fork);
			free(philos[i].fork);
		}
		if (philos[i].meal)
		{
			pthread_mutex_destroy(philos[i].meal);
			free(philos[i].meal);
		}
	}
	free(philos);
}
int	main(int ac, char **av)
{
	t_philo	*philos;
	t_box	box;

	if (!ft_check_input(ac, av))
		return (1);
	if (!ft_fill_box(ac, av, &box))
		return (1);
	philos = malloc(sizeof(t_philo) * box.nb_of_philos);
	if (!philos)
	{
		ft_putstr_fd("Failed to allocate memory for philosophers\n", 2);
		return (1);
	}
	if (!ft_set_mutex(philos, &box))
	{
		free(philos);
		return (1);
	}
	ft_set_all(philos, &box);
	ft_threading(philos, &box);
	ft_cleanup(philos, &box);
	return (0);
}