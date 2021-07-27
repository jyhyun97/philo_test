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