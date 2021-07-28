#include "philo.h"

int ft_atoi(const char *str)
{
	int	i;
	int	rst;
	int	pmsign;

	i = 0;
	rst = 0;
	pmsign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			pmsign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		rst = (rst * 10) + (str[i] - '0');
		i++;
	}
	return (rst * pmsign);
}

unsigned long	get_time(void)
{
	struct timeval  tmp;
	unsigned long	new;
	
	gettimeofday(&tmp, 0);	
	new = tmp.tv_sec * 1000;
	new += tmp.tv_usec / 1000;
	//1 second = 1000ms 
	//1 ms = 1000us
	return (new);
}


void	print_msg(t_philo *philo, int flag)
{
	pthread_mutex_lock(philo->data->print);
	if (flag == FORK)
		printf("[%lu] %d has taken a fork\n", get_time() - philo->data->start_time, philo->num);
	else if (flag == EAT)
		printf("[%lu] %d is eating\n", get_time() - philo->data->start_time, philo->num);
	else if (flag == SLEEP)
    	printf("[%lu] %d is sleeping\n", get_time() - philo->data->start_time, philo->num);	
    else if (flag == THINK)
    	printf("[%lu] %d is thinking\n", get_time() - philo->data->start_time, philo->num);
	else if (flag == DIE)
	{
		if (*(philo->data->death) == 1)
			printf("[%lu] %d is died\n", get_time() - philo->data->start_time, philo->num);
	}
	pthread_mutex_unlock(philo->data->print);
}