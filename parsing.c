

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

void initial_data(t_data *data,int ac,char **av)
{
    if (check_only_num(av) && valid_num(ac, av))
    {
        data->number_of_philosophers = my_atoi(av[1]);
        data->time_to_die = my_atoi(av[2]);
        data->time_to_eat = my_atoi(av[3]);
        data->time_to_sleep = my_atoi(av[4]);
		data->all_philos_eat = 0;
		data->a_philo_dead = 0;
        if (ac == 6)
            data->number_of_times_each_philosopher_must_eat = my_atoi(av[5]);
        else
            data->number_of_times_each_philosopher_must_eat = -1;
    } else
		print_err("should be valid num");

}