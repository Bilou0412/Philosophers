#include "philo.h"

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
		ft_usleep(1);
	while (1)
	{
		philo_eat(philo_cast);
		philo_sleep(philo_cast);
	}
	return (NULL);
}
int	main(int argc, char **argv)
{
	int i;
	t_philo philo[250];
	t_mutex_and_death_f mutex_death_f;

	mutex_death_f.death = 0;
	i = 0;
	if (argc < 5 || argc > 6 || invalid_arg(argv))
		return (printf("Program take the following arguments:\n number_of_philosophers : [MIN 1 ; MAX 200]\n time_to_die : MIN 1 \n time_to_eat : MIN 1\n time_to_sleep : MIN 1\n [number_of_times_each_philosopher_must_eat]\n"),
			0);
	if (init_data(philo, &mutex_death_f, argv) < 0)
		return (-1);
	if (wait_philo(philo) < 0)
		return (-1);
	return (0);
}