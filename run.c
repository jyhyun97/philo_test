#include "philo.h"

void *thread_run(void *philo_imsi)
{
    t_philo *philo;
    
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
		if (philo->num % 2 == 1)
		{
			//왼쪽 포크
			pthread_mutex_lock(philo->l_fork);
			if (*(philo->data->death) == 0 && philo->my_death == 0)
				print_msg(philo, FORK);
			else
				break;
			//오른쪽 포크
			pthread_mutex_lock(philo->r_fork);
			if (*(philo->data->death) == 0 && philo->my_death == 0)
				print_msg(philo, FORK);
			else
				break;
		}
		else
		{
			//오른쪽 포크
			pthread_mutex_lock(philo->r_fork);
			if (*(philo->data->death) == 0 && philo->my_death == 0)
				print_msg(philo, FORK);
			else
				break;
			//왼쪽 포크
			pthread_mutex_lock(philo->l_fork);
			if (*(philo->data->death) == 0 && philo->my_death == 0)
				print_msg(philo, FORK);
			else
				break;
		}
		//먹는다 출력
		if (*(philo->data->death) == 0 && philo->my_death == 0)
			print_msg(philo, EAT);
		else
			break;
		++philo->eat_count;
		if (philo->data->must_eat_count == philo->eat_count)
		{
			pthread_mutex_unlock(philo->l_fork);
			pthread_mutex_unlock(philo->r_fork);
			return (0);
		}
		philo->last_eat = get_time();
		pthread_mutex_lock(philo->eating);
		//usleep(philo->data->time_to_eat * 1000);//while get time이 time to eat 만큼 돌리기
		//while (get_time() - last_eat < time_to_eat){}
		while (get_time() - philo->last_eat < (unsigned long)philo->data->time_to_eat)
		{
			
		}
		pthread_mutex_unlock(philo->eating);
		//포크 내려놓는다
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		
		//잔다
		if (*(philo->data->death) == 0 && philo->my_death == 0)
			print_msg(philo, SLEEP);
		else
			break;
		unsigned long sleep_tmp =  get_time();
		while (get_time() - sleep_tmp < (unsigned long)philo->data->time_to_sleep)
		{}
		//생각한다
		if (*(philo->data->death) == 0 && philo->my_death == 0)
			print_msg(philo, THINK);
		else
			break;
	}
	return ((void *)0);
}