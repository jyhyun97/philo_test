#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

# define FORK 1
# define EAT 2
# define SLEEP 3
# define THINK 4
# define DIE 5

typedef struct  s_data
{
    //공용
    unsigned long     start_time;//unsigned long
    int     num_of_philo;
    int     time_to_eat;
    int     time_to_die;
    int     time_to_sleep;
    int     must_eat_count;
    int     *death;
    pthread_mutex_t *death_mutex;//int *

    pthread_mutex_t *print;
    pthread_mutex_t *fork;
    //t_philo *philo;
}   t_data;

typedef struct  s_philo
{
    //단독
    int     num;
    unsigned long     last_eat;
    int     eat_count;
    int     my_death;
    pthread_t thread;
    pthread_t monitor;

    pthread_mutex_t *eating;
    pthread_mutex_t *l_fork;
    pthread_mutex_t *r_fork;
    t_data  *data;
}   t_philo;

int	ft_atoi(const char *str);
int check_input(int argc, char *argv[]);
int init_data(char *argv[], t_data *data);
int init_philo(t_data *data, t_philo *philo);
int init_thread(t_data *data, t_philo *philo);

void *thread_run(void *philo_imsi);
void *thread_monitor(void *philo_imsi);

unsigned long	get_time(void);
void	print_msg(t_philo *philo, int flag);






#endif