#include "philo.h"

void	init_data_from_arg(t_philo philo[], t_mutex_and_death_f *mutex_death_f,
		char **arg)
{
	int	i;

	i = 0;
	while (i < ft_atoi(arg[1]))
	{
		philo[i].id = i + 1;
		philo[i].death = &mutex_death_f->death;
		philo[i].number_of_philosophers = ft_atoi(arg[1]);
		philo[i].time_to_die = ft_atoi(arg[2]);
		philo[i].time_to_eat = ft_atoi(arg[3]);
		philo[i].time_to_sleep = ft_atoi(arg[4]);
		philo[i].number_of_times_each_philosopher_must_eat = 0;
		philo[i].nb_eat = 0;
		philo[i].last_eating = 0;
		philo[i].start = get_current_time();
		pthread_mutex_init(&philo->mutex_fork_left, NULL);
		i++;
	}
}

int	init_data_mutex_and_thread(t_philo philo[],
		t_mutex_and_death_f *mutex_death_f)
{
	int	i;

	i = 0;
	if (pthread_mutex_init((&mutex_death_f->mutex_death), NULL)
		|| pthread_mutex_init(&mutex_death_f->mutex_eat, NULL)
		|| pthread_mutex_init(&mutex_death_f->mutex_write, NULL))
		return (-1);
	while (i < philo->number_of_philosophers)
	{
		if (i == 0)
		{
			philo[i].mutex_fork_right = &philo[philo[i].number_of_philosophers - 1].mutex_fork_left;
		}
		else
			philo[i].mutex_fork_right = &philo[i + 1].mutex_fork_left;
		philo[i].mutex_eat = &mutex_death_f->mutex_eat;
		philo[i].mutex_write = &mutex_death_f->mutex_write;
		philo[i].mutex_death = &mutex_death_f->mutex_death;
		if (pthread_create(&philo[i].thread, NULL, (void *)&routine, &philo[i]))
			return (-1);
		i++;
	}
	return (0);
}

int	init_data(t_philo philo[], t_mutex_and_death_f *mutex_death_f, char **arg)
{
	init_data_from_arg(philo, mutex_death_f, arg);
	if (init_data_mutex_and_thread(philo, mutex_death_f))
		return (-1);
	return (0);
}
