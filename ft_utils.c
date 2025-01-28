#include "philo.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s || fd < 0)
		return ;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

int	ft_is_number(char *str)
{
	int	j;

	j = 0;
	while (str[j])
	{
		if ((str[j] >= '0' && str[j] <= '9'))
			j++;
		else
			return (0);
	}
	return (1);
}

long	ft_atoi(char *str)
{
	long	re;

	re = 0;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (!ft_is_number(str))
		return (-1);
	while (*str >= '0' && *str <= '9')
	{
		if (re > INT_MAX)
			return (-1);
		re = re * 10 + *str - '0';
		str++;
	}
	return (re);
}

void	ft_set_all(t_philo *philos, t_box *box)
{
	int	i;

	i = 0;
	box->stoop = 0;
	box->dead = 0;
	box->philos = philos;
	while (i < box->nb_of_philos)
	{
		philos[i].index = i + 1;
		philos[i].meals_count = 0;
		philos[i].eating = 0;
		philos[i].info = box;
		philos[i].time = get_live_time();
		philos[i].time_last_meal = get_live_time();
		i++;
	}
}
