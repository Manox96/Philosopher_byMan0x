#include "philosopher.h"
#include <stdio.h>

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

void print_err(char *str)
{
	printf("%s",str);
	exit(0);
}


char *parsing_inputs(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			print_err("should be only number");
		i++;
	}
	i = 0;
	while (str[i] >= 9 && (str[i] <= 13 || str[i] == 32))
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
		print_err("shoul be posotive number");
	return str;
}

int	my_atoi(char *str)
{
	int	i;
	int	r;

	i = 0;
	r = 0;
	str = parsing_inputs(str);
	while (str[i] >= '0' && str[i] <= '9')
	{
		r = r * 10 + str[i] - '0';
		i++;
	}
	return (r);
}
