

#include "philosopher.h"

void initial_data(t_data *data,int ac,char **av)
{
    data->number_of_philosophers = my_atoi(av[1]);
    data->time_to_die = my_atoi(av[2]);
	data->time_to_eat = my_atoi(av[3]);
	data->time_to_sleep = my_atoi(av[4]);
    if (ac == 6)
        data->number_of_times_each_philosopher_must_eat = my_atoi(av[5]);
    else
        data->number_of_times_each_philosopher_must_eat = 0;

}