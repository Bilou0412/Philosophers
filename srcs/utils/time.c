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
	while ((get_current_time() - start) < milliseconds)
	{
		pthread_mutex_lock(philo->mutex_eat);
		if ((get_current_time() - philo->last_eating) > philo->time_to_die)
		{
			pthread_mutex_unlock(philo->mutex_eat);
			philo_write(philo, "died");
			pthread_mutex_lock(philo->mutex_death);
			*philo->death = 1;
			pthread_mutex_unlock(philo->mutex_death);
			pthread_mutex_lock(philo->mutex_eat);
		}
		pthread_mutex_unlock(philo->mutex_eat);
		pthread_mutex_lock(philo->mutex_eat);
		if (*philo->m_eat > philo->number_of_philosophers
			* philo->number_of_times_each_philosopher_must_eat)
		{
			*philo->eat_finish = 1;
		}
		pthread_mutex_unlock(philo->mutex_eat);
		usleep(500);
	}
	return (0);
}
