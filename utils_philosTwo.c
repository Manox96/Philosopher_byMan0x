
#include "philosopher.h"
#include <stdlib.h>


void createPhilo(t_data *data)
{
    int i;

    i = 0;
    data->forks = malloc(sizeof(pthread_mutex_t) * data->number_of_philosophers);
    if (!data->forks)
        print_err("malloc Error");
    while (i < data->number_of_philosophers)
        if (pthread_mutex_init(&(data->forks[i]), NULL))
			print_err("mutex faild !!");
    if (pthread_mutex_init(&(data->what_he_do), NULL))
			print_err("mutex faild !!");
    if (pthread_mutex_init(&(data->death), NULL))
			print_err("mutex faild !!");
    if (pthread_mutex_init(&(data->all_eat), NULL))
			print_err("mutex faild !!");
    if (pthread_mutex_init(&(data->eaten_times), NULL))
			print_err("mutex faild !!");
}