/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoudach <bmoudach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 12:00:24 by bmoudach          #+#    #+#             */
/*   Updated: 2023/12/27 12:44:03 by bmoudach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	destroy_mutex(t_mutex_and_death_f *mutex_death_f, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo[0].number_of_philosophers)
	{
		pthread_mutex_destroy(&philo[i].mutex_fork_right);
		i++;
	}
	pthread_mutex_destroy(&mutex_death_f->mutex_death);
	pthread_mutex_destroy(&mutex_death_f->mutex_eat);
	pthread_mutex_destroy(&mutex_death_f->mutex_write);
	pthread_mutex_destroy(&mutex_death_f->mutex_start);
	return (0);
}

int	check_dead(t_philo *philo)
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
	while (!check_dead(philo) && (!*(philo_cast->eat_finish)
			|| philo_cast->nb_times_philosopher_must_eat == -1))
	{
		if (philo_cast->id % 2 == 0)
			philo_eat(philo_cast);
		else
			philo_eat_odd(philo_cast);
		philo_sleep(philo_cast);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	int					i;
	t_philo				philo[300];
	t_mutex_and_death_f	mutex_death_f;
	pthread_t			monitoring;

	mutex_death_f.death = 0;
	mutex_death_f.eat_finish = 0;
	i = 0;
	if (argc < 5 || argc > 6 || invalid_arg(argv))
	{
		printf("ERROR\nnb_philo\ntime_die\ntime_eat\ntime_sleep\nnb_meal\n");
		return (0);
	}
	if (init_data(philo, &mutex_death_f, argv) < 0)
		return (-1);
	pthread_create(&monitoring, NULL, (void *)&monitor, philo);
	pthread_join(monitoring, NULL);
	if (wait_philo(philo) < 0)
		return (-1);
	if (destroy_mutex(&mutex_death_f, philo))
		return (-1);
}
