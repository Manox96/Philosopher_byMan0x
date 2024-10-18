
#include "philosopher.h"
#include <stdlib.h>



void	free_all(t_data *dt)
{
	free(dt->fork);
	free(dt->philo);
}


long long	get_time(t_time time_MOS)
{
	struct timeval	time;

	if (!gettimeofday(&time, NULL))
        print_err("gettimeofday Error");
    if (time_MOS == SECOND)
        return (time.tv_sec + (time.tv_usec / 1e6));
    else if (time_MOS == MILLISECOND)
        return (time.tv_sec * 1e3 + (time.tv_usec / 1e3));
    else if (time_MOS == MICROSECOND)
        return (time.tv_sec * 1e6 + time.tv_usec);
    else
        print_err("time Error");
    return (0);
}

// void createPhilo(t_data *data)
// {
//     int i;

//     i = -1;
//     data->philos = ft_malloc(sizeof(t_philo) * data->number_of_philosophers);
//     data->forks = ft_malloc(sizeof(pthread_mutex_t) * data->number_of_philosophers);
//     if (!data->forks)
//         print_err("malloc Error");
//     while (++i < data->number_of_philosophers)
//     {
//         if (pthread_mutex_init(&(data->forks[i]), NULL))
// 			print_err("mutex faild !!");
//     }
//     if (pthread_mutex_init(&(data->what_he_do), NULL))
// 			print_err("mutex faild !!");
//     if (pthread_mutex_init(&(data->death), NULL))
// 			print_err("mutex faild !!");
//     if (pthread_mutex_init(&(data->all_eat), NULL))
// 			print_err("mutex faild !!");
//     if (pthread_mutex_init(&(data->eaten_times), NULL))
// 			print_err("mutex faild !!");
// }
