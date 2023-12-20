/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoudach <bmoudach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 23:11:00 by bmoudach          #+#    #+#             */
/*   Updated: 2023/12/20 16:01:21 by bmoudach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_write(t_philo *philo, char *str)
{
	pthread_mutex_lock(philo->mutex_write);
	printf("%lu %d %s\n", (get_current_time() - philo->start), philo->id, str);
	pthread_mutex_unlock(philo->mutex_write);
}
void	philo_eat(t_philo *philo)
{
	
	pthread_mutex_lock(&philo->mutex_fork_left);
	philo_write(philo, "has taken a fork");
	if (philo->number_of_philosophers == 1)
	{
		ft_usleep(philo->time_to_die);
		pthread_mutex_unlock(philo->mutex_fork_right);
		return ;
	}
	pthread_mutex_lock(philo->mutex_fork_right);
	philo_write(philo, "has taken a fork");
	philo_write(philo, "is eating");
	pthread_mutex_lock(philo->mutex_eat);
	philo->last_eating = get_current_time();
	philo->nb_eat++;
	pthread_mutex_unlock(philo->mutex_eat);
	ft_usleep(philo->time_to_eat);
	pthread_mutex_unlock(philo->mutex_fork_right);
	pthread_mutex_unlock(&philo->mutex_fork_left);
}
void	philo_sleep(t_philo *philo)
{
	philo_write(philo, "is sleeping");
	ft_usleep(philo->time_to_sleep);
	philo_write(philo, "is thinking");
}
void	philo_death(t_philo *philo)
{
	pthread_mutex_lock(philo->mutex_death);
	*philo->death = 1;
	philo_write(philo, "died");
	pthread_mutex_unlock(philo->mutex_death);
}