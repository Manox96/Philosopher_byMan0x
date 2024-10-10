

#include "philosopher.h"

int	check_only_num(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (j == 0 && av[i][j] == '+')
				j++;
			if (!ft_isdigit(av[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	valid_num(int ac, char **av)
{
	int	i;
	int	stp;

	i = 1;
	stp = 4;
	if (ac == 6)
		stp = 5;
	while (i < stp)
	{
		if ((my_atoi(av[i]) <= 0 || my_atoi(av[i]) >= INT_MAX))
			return (0);
		i++;
	}
	return (1);
}

void initial_inputs(t_data *data,int ac,char **av)
{
    if (check_only_num(av) && valid_num(ac, av))
    {
        data->nbrs_philo = my_atoi(av[1]);
        data->time_to_die = my_atoi(av[2]);
        data->time_to_eat = my_atoi(av[3]);
        data->time_to_sleep = my_atoi(av[4]);
        if (ac == 6)
            data->must_eat = my_atoi(av[5]);
        else
            data->must_eat = -1;
    } else
		print_err("should be valid num");
	
}

void philo_init(t_data *data)
{
	int i;
	t_philo *philo;

	i = -1;
	while (++i < data->nbrs_philo)
	{
		philo = data->philo + i;
		philo->id_philo = i;
		philo->is_fulll = 0;
		philo->meals_c = 0;
		philo->data = data;
		philo->left_fork = &data->fork[(i + 1) % data->nbrs_philo]; 
		philo->right_fork = &data->fork[i];
		if (philo->id_philo % 2 == 0)
		{
			philo->left_fork = &data->fork[i];
			philo->right_fork = &data->fork[(i + 1) % data->nbrs_philo]; 
		}
	}
}

void intial_data(t_data *data)
{
	int	i;

	i = -1;
	data->end_sum = 0;
	data->philo = ft_malloc(sizeof(t_philo) * data->nbrs_philo); 
	data->fork = ft_malloc(sizeof(t_fork) * data->nbrs_philo); 
	while (++i < data->nbrs_philo)
	{
		handle_mutex(INIT,&data->fork[i].fork);
		data->fork->fork_id = i;
	}
	philo_init(data);
    
}