#include "philo.h"

int	dead_loop(t_philo *philo)
{
	pthread_mutex_lock(philo->mutex_death);
	if (*philo->death == 1)
		return (pthread_mutex_unlock(philo->mutex_death), 1);
	pthread_mutex_unlock(philo->mutex_death);
	return (0);
}
int	wait_philo(t_philo philo[])
{
	int	i;

	i = 0;
	while (i < philo->number_of_philosophers)
	{
		if (pthread_join(philo[i].thread, NULL))
			return (-1);
		i++;
	}
	return (0);
}

void	*routine(void *philo)
{
	t_philo	*philo_cast;

	philo_cast = (t_philo *)philo;
	if (philo_cast->id % 2 == 0)
		ft_usleep(1, philo);
	while (!dead_loop(philo) && (!*(philo_cast->eat_finish)
			|| philo_cast->number_of_times_each_philosopher_must_eat == -1))
	{
		philo_eat(philo_cast);
		philo_sleep(philo_cast);
	}
	return (NULL);
}
int	main(int argc, char **argv)
{
	int i;
	t_philo philo[300];
	t_mutex_and_death_f mutex_death_f;
	pthread_t monitoring;

	mutex_death_f.death = 0;
	mutex_death_f.eat_finish = 0;
	i = 0;
	if (argc < 5 || argc > 6 || invalid_arg(argv))
		return (printf("Program take the following arguments:\n number_of_philosophers : [MIN 1 ; MAX 200]\n time_to_die : MIN 1 \n time_to_eat : MIN 1\n time_to_sleep : MIN 1\n [number_of_times_each_philosopher_must_eat]\n"),
			0);
	if (init_data(philo, &mutex_death_f, argv) < 0)
		return (-1);
	pthread_create(&monitoring, NULL, (void *)&monitor, philo);
	pthread_join(monitoring, NULL);
	if (wait_philo(philo) < 0)
		return (-1);

	return (0);
}