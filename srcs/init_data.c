#include "philo.h"

void	init_data(t_philo philo[], char **arg)
{
	int	number_of_philo;
	int	i;

	number_of_philo = ft_atoi(arg[1]);
	i = 0;
	while (i < number_of_philo)
	{
		philo[i].id = i + 1;
		philo[i].number_of_philosophers = ft_atoi(arg[1]);
		philo[i].time_to_die = ft_atoi(arg[2]);
		philo[i].time_to_eat = ft_atoi(arg[3]);
		philo[i].time_to_sleep = ft_atoi(arg[4]);
		philo[i].number_of_times_each_philosopher_must_eat = 0;
		if (arg[5])
			philo[i].number_of_times_each_philosopher_must_eat = ft_atoi(arg[5]);
		i++;
	}
	philo[i] = (t_philo){0};
}
