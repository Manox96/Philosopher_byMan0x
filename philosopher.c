#include "philosopher.h"
#include <stdio.h>

int main(int ac, char **av)
{
	t_data data;
	if (ac != 5 && ac != 6)
		print_err("should be 5 or 4 args");
	initial_data(&data, ac, av);
	
	printf("%d\n",data.time_to_eat);
	printf("%d\n",data.time_to_die);
	printf("%d\n",data.time_to_sleep);
	printf("%d\n",data.number_of_times_each_philosopher_must_eat);
	printf("%d\n",data.a_philo_dead);
	printf("%d\n",data.all_philos_eat);

	puts("ok");


}