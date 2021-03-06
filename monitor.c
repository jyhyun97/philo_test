#include "philo.h"

void *thread_monitor(void *philo_imsi)
{
    t_philo *philo;
    philo = philo_imsi;

    while(*(philo->data->death) == 0 && philo->my_death == 0 && philo->data->must_eat_count != philo->eat_count)
    {
        if (philo->data->must_eat_count != philo->eat_count && get_time() - philo->last_eat > (unsigned long)philo->data->time_to_die)
        {
            ++*(philo->data->death);
            philo->my_death = 1;
        }
        usleep(100);
    }
    if (philo->my_death == 1 && *(philo->data->death) == 1)
		print_msg(philo, DIE);
    return ((void *)0);
}