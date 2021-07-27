#include "philo.h"

int main(int argc, char *argv[])
{
    t_philo *philo;
    t_data  data;

    if (check_input(argc, argv) != 0)
        return (0);
    init_data(argc, argv, &data);
    philo = (t_philo *)malloc(sizeof(t_philo) * data.num_of_philo);
    if (philo == 0)
        return (1);
    init_philo(&data, philo);
    init_thread(&data, philo);
    return (0);
}