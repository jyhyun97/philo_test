#include "philo.h"

int do_eat(t_philo *philo)
{
	if (*(philo->data->death) == 0 && philo->my_death == 0 && philo->num % 2 == 1)
	{
		if (*(philo->data->death) == 0 && philo->my_death == 0)
		{
			pthread_mutex_lock(philo->l_fork);
			print_msg(philo, FORK);
		}
		else
		{
			return (1);
		}
		if (*(philo->data->death) == 0 && philo->my_death == 0)
		{
			pthread_mutex_lock(philo->r_fork);
			print_msg(philo, FORK);
		}
		else
		{
			pthread_mutex_unlock(philo->l_fork);
			return (1);
		}
	}
	else if (*(philo->data->death) == 0 && philo->my_death == 0)
	{
		if (*(philo->data->death) == 0 && philo->my_death == 0)
		{	
			pthread_mutex_lock(philo->r_fork);
			print_msg(philo, FORK);
		}
		else
		{
			return (1);
		}
		if (*(philo->data->death) == 0 && philo->my_death == 0)
		{
			pthread_mutex_lock(philo->l_fork);
			print_msg(philo, FORK);
		}
		else
		{
			pthread_mutex_unlock(philo->r_fork);
			return (1);
		}
	}
	if (*(philo->data->death) == 0 && philo->my_death == 0)
		print_msg(philo, EAT);
	else
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		return (1);
	}
	++philo->eat_count;
	if (philo->data->must_eat_count == philo->eat_count)
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		return (2);//바로 스레드 종료
	}
	philo->last_eat = get_time();
	while (*(philo->data->death) == 0 && philo->my_death == 0 && get_time() - philo->last_eat < (unsigned long)philo->data->time_to_eat)
	{	
	}
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	return (0);
}

int do_sleep(t_philo *philo)
{
	unsigned long sleep_tmp;

	if (*(philo->data->death) == 0 && philo->my_death == 0)
		print_msg(philo, SLEEP);
	else
		return (1);
	sleep_tmp =  get_time();
	while (*(philo->data->death) == 0 && philo->my_death == 0 && get_time() - sleep_tmp < (unsigned long)philo->data->time_to_sleep)
	{
	}
	return (0);
}

void *thread_run(void *philo_imsi)
{
    t_philo *philo;
	int		eat_tmp;
    
	philo = philo_imsi;
	if (philo->data->must_eat_count == 0)
		return (0);	
	if (philo->data->num_of_philo == 1)
	{	
		philo->my_death = 1;
		*(philo->data->death) = 1;
	}
    while (*(philo->data->death) == 0 && philo->my_death == 0)
	{
		eat_tmp = do_eat(philo);
		if (eat_tmp == 1)
			break;
		else if (eat_tmp == 2)
			return (0);
		//잔다
		if (do_sleep(philo) == 1)
			break;
		//생각한다
		if (*(philo->data->death) == 0 && philo->my_death == 0)
			print_msg(philo, THINK);
		else
			break;
	}
	return ((void *)0);
}