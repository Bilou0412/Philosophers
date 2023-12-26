/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoudach <bmoudach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 01:59:14 by bmoudach          #+#    #+#             */
/*   Updated: 2023/12/22 16:28:30y bmoudach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	finish_eat(t_philo *philo)
{
	int	i;

	i = 0;
	if (philo[0].number_of_times_each_philosopher_must_eat == -1)
		return (0);
	while (i < philo[i].number_of_philosophers)
	{
		pthread_mutex_lock(philo[i].mutex_eat);
		if (philo[i].nb_eat < philo->number_of_times_each_philosopher_must_eat)
			return (pthread_mutex_unlock(philo[i].mutex_eat), 0);
		pthread_mutex_unlock(philo[i].mutex_eat);
		i++;
	}
	pthread_mutex_lock(philo[0].mutex_eat);
	*philo[0].eat_finish = 1;
	pthread_mutex_unlock(philo[0].mutex_eat);
	return (1);
}
int	is_dead(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo[0].number_of_philosophers)
	{
		/*pthread_mutex_lock(philo[i].mutex_eat);
		printf("last eating %lu time to eat %lu id %d\n", (get_current_time()
				- philo[i].last_eating),
			philo[i].time_to_die,philo[i].id);
		pthread_mutex_unlock(philo[i].mutex_eat);*/
		pthread_mutex_lock(philo[0].mutex_eat);
		if ((get_current_time() - philo[i].last_eating) >= philo[i].time_to_die)
		{
			pthread_mutex_unlock(philo[0].mutex_eat);
			pthread_mutex_lock(philo[0].mutex_write);
			printf("%lu %d %s\n", (get_current_time() - philo->start),
				philo[i].id, "died");
			pthread_mutex_unlock(philo[0].mutex_write);
			pthread_mutex_lock(philo[0].mutex_death);
			*philo[0].death = 1;
			pthread_mutex_unlock(philo[0].mutex_death);
			return (1);
		}
		pthread_mutex_unlock(philo[0].mutex_eat);
		i++;
	}
	return (0);
}

void	*monitor(t_philo *philo)
{
	while (1)
	{
		if (is_dead(philo) || finish_eat(philo))
			break ;
	}
	return (philo);
}

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}
int	ft_usleep(size_t milliseconds, t_philo *philo)
{
	size_t	start;

	start = get_current_time();
	pthread_mutex_lock(philo->mutex_death);
	while ((get_current_time() - start) < milliseconds && !*philo->death)
	{
		pthread_mutex_unlock(philo->mutex_death);
		usleep(500);
		pthread_mutex_lock(philo->mutex_death);
	}
	pthread_mutex_unlock(philo->mutex_death);
	return (0);
}
