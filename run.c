#include "philo.h"

void *thread_run(void *philo_imsi)
{
    t_philo *philo;
    philo = philo_imsi;
    printf("[%d] philo running\n", philo->num);
	//while(death == 0 && my_death == 0)
		//if (death == 0 ~~~ )
			//왼포크 오른포크 들고 print
			//last eat 갱신
			//먹기()print eat -> usleep 먹는 시간
		//if (death == 0 ~~~ )
			//왼포크 오른포크 unlock
			//자기()print -> usleep 자는 시간
		//if (death == 0 ~~~ )
			//생각하기(대기) print think
	//if (my_death == 1)
		//print 나 죽었음	
	return ((void *)0);
}