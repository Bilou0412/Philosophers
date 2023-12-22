/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoudach <bmoudach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 23:11:00 by bmoudach          #+#    #+#             */
/*   Updated: 2023/12/22 16:48:22 by bmoudach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_write(t_philo *philo, char *str)
{
	pthread_mutex_lock(philo->mutex_write);
	pthread_mutex_lock(philo->mutex_death);
	if (!*philo->death)
	{
		pthread_mutex_unlock(philo->mutex_death);
		printf("%lu %d %s\n", (get_current_time() - philo->start), philo->id,
			str);
		pthread_mutex_lock(philo->mutex_death);
	}
	pthread_mutex_unlock(philo->mutex_death);
	pthread_mutex_unlock(philo->mutex_write);
}
void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->mutex_fork_right);
	philo_write(philo, "has taken a fork");
	pthread_mutex_lock(&(philo->mutex_fork_left));
	philo_write(philo, "has taken a fork");
	philo_write(philo, "is eating");
	pthread_mutex_lock(philo->mutex_eat);
	philo->nb_eat++;
	pthread_mutex_unlock(philo->mutex_eat);
	ft_usleep(philo->time_to_eat, philo);
	philo->last_eating = get_current_time();
	pthread_mutex_unlock(&(philo->mutex_fork_left));
	pthread_mutex_unlock(philo->mutex_fork_right);
}
void	philo_eat_odd(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex_fork_left);
	philo_write(philo, "has taken a fork");
	if (philo->number_of_philosophers == 1)
	{
		ft_usleep(philo->time_to_die, philo);
		pthread_mutex_unlock(philo->mutex_fork_right);
		return ;
	}
	pthread_mutex_lock(philo->mutex_fork_right);
	philo_write(philo, "has taken a fork");
	philo_write(philo, "is eating");
	pthread_mutex_lock(philo->mutex_eat);
	philo->nb_eat++;
	pthread_mutex_unlock(philo->mutex_eat);
	ft_usleep(philo->time_to_eat, philo);
	philo->last_eating = get_current_time();
	pthread_mutex_unlock(philo->mutex_fork_right);
	pthread_mutex_unlock(&(philo->mutex_fork_left));
}
void	philo_sleep(t_philo *philo)
{
	philo_write(philo, "is sleeping");
	ft_usleep(philo->time_to_sleep, philo);
	philo_write(philo, "is thinking");
	ft_usleep(1, philo);
}