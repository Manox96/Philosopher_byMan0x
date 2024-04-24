#include "philosopher.h"
#include <stdio.h>

int main(int ac, char **av)
{
	t_data data;
	if (ac != 5 && ac != 6)
	{
		perror("should be 5 or 4 args");
		return (0);
	}
	initial_data(&data, ac, av);
	printf("%d\n",data.number_of_philosophers);
	printf("%d\n",data.time_to_die);
	printf("%d\n",data.time_to_eat);
	printf("%d\n",data.time_to_sleep);
	printf("%d\n",data.number_of_times_each_philosopher_must_eat);
	
	puts("ok");


}