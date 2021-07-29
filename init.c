#include "philo.h"

int check_input(int argc, char *argv[])
{
    int i;
    int j;

    if (argc < 5 || argc > 6)
    {
        printf("Error\n");
        return (1);
    }
    i = 1;
    while (argv[i] != 0)
    {
        j = 0;
        while (argv[i][j] != '\0')
        {
            if(argv[i][j] < '0' || argv[i][j] > '9')
                return (1);
            j++;
        }
        i++;
    }
    return (0);
}

int init_data(char *argv[], t_data *data)
{
    int i;

    i = 0;
    data->num_of_philo = ft_atoi(argv[1]);
    data->time_to_die = ft_atoi(argv[2]);
    data->time_to_eat = ft_atoi(argv[3]);
    data->time_to_sleep = ft_atoi(argv[4]);
    if (argv[5] != 0)
        data->must_eat_count = ft_atoi(argv[5]);
    else
        data->must_eat_count = -1;
    data->death = (int *)malloc(sizeof(int) * 1);
    *(data->death) = 0;
    data->death_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * 1);
    pthread_mutex_init(data->death_mutex, 0);
    data->print = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * 1);
    pthread_mutex_init(data->print, 0);
    data->fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * data->num_of_philo);
    if (data->fork == 0)
        return (1);
    while (i < data->num_of_philo)
    {
        pthread_mutex_init(&data->fork[i], 0);    
        ++i;
    }
    return (0);
}

int init_philo(t_data *data, t_philo *philo) 
{
    int i;

    i = 0;
    while (i < data->num_of_philo)
    {
        philo[i].data = data;
        philo[i].num = i + 1;
        philo[i].eat_count = 0;
        philo[i].l_fork = &(data->fork[i]);
        if (i == data->num_of_philo - 1)
            philo[i].r_fork = &(data->fork[0]);
        else
            philo[i].r_fork = &(data->fork[i + 1]);
        ++i;
    }
    return (0);
}

int init_thread(t_data *data, t_philo *philo)
{
    int             i;

    data->start_time = get_time();
    i = 0;
    while (i < data->num_of_philo)
    {
        philo[i].last_eat = data->start_time;
        pthread_create(&(philo[i].thread), NULL, &thread_run, &(philo[i]));
        pthread_create(&(philo[i].monitor), NULL, &thread_monitor, &(philo[i]));
        usleep(100);
        ++i;
    }
    i = 0;
    while (i < data->num_of_philo)
    {
        pthread_join(philo[i].thread, NULL);
        pthread_join(philo[i].monitor, NULL);
        pthread_mutex_destroy(&(data->fork[i]));
        i++;
    }
    pthread_mutex_destroy(data->print);
    free(data->fork);
    free(data->print);
    free(data->death);
    return (0);
}