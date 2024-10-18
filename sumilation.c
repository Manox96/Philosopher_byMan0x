#include "philosopher.h"


void set_m(pthread_mutex_t *mtx,int *dest, int value)
{
    handle_mutex(LOCK, mtx);
    *dest = value;
    handle_mutex(UNLOCK, mtx);
}

int get_m(pthread_mutex_t *mtx, int *value)
{
    int ret;

    handle_mutex(LOCK, mtx);
    ret = *value;
    handle_mutex(UNLOCK, mtx);
    return (ret);

}
int simulation_end(t_data *data)
{
    return get_m(&data->dt_mutex, &data->end_sum);
}


void    *start_dinner(void *data)
{
    t_philo *dt = (t_philo *)data;
    // wail_all_thread;

    while (!simulation_end(dt->data))
    {
        if (dt->is_fulll)
            break;
        // eat(dt);
        
        // thinkind(dt);
    }



}
void start_sumilation(t_data *data)
{
    int i = 0;
    if (data->nbrs_philo == 0)
        return;
    else if (data->nbrs_philo == 1)
    {
        
    }
    else
    {
        while (i++ < data->nbrs_philo)
            handle_thread(&data->philo[i].thread_id, start_dinner, data, CREATE);
    }
    data->start_sum = get_time(MILLISECOND);
    set_m(&data->dt_mutex, &data->start_sum, 1);
    while (i++ < data->nbrs_philo)
        handle_thread(&data->philo[i].thread_id, NULL, NULL, JOIN);


}