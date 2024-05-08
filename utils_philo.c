#include "philosopher.h"
#include <stdio.h>

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

int my_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	print_err(char *str)
{
	write(2, "Error\n", 6);
	write(2, str, my_strlen(str));
	exit(1);
}


int	my_atoi(char *str)
{
	int			i;
	long		s;
	long		r;

	r = 0;
	s = 1;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			s = s * -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		r = r * 10 + str[i] - '0';
		if ((r * s) > INT_MAX || (r * s) < INT_MIN)
			print_err("the number should be MIN_INT < numer < MAX_INT");
		i++;
	}
	return (s * r);
}
