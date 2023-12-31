/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoudach <bmoudach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 12:25:19 by bmoudach          #+#    #+#             */
/*   Updated: 2023/12/27 12:26:48 by bmoudach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		philo[i].nb_eat = 0;
		philo[i].eat_finish = &mutex_death_f->eat_finish;
		philo[i].number_of_philosophers = ft_atoi(arg[1]);
		philo[i].time_to_die = ft_atoi(arg[2]);
		philo[i].time_to_eat = ft_atoi(arg[3]);
		philo[i].time_to_sleep = ft_atoi(arg[4]);
		philo[i].nb_times_philosopher_must_eat = -1;
		if (arg[5])
			philo[i].nb_times_philosopher_must_eat = ft_atoi(arg[5]);
		philo[i].time_philo_is_dead = 0;
		philo[i].start = get_current_time();
		philo[i].last_eating = get_current_time();
		pthread_mutex_init(&philo[i].mutex_fork_right, NULL);
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
		|| pthread_mutex_init(&mutex_death_f->mutex_write, NULL)
		|| pthread_mutex_init(&mutex_death_f->mutex_start, NULL))
		return (-1);
	while (i < philo->number_of_philosophers)
	{
		if (i + 1 == philo->number_of_philosophers)
			philo[i].mutex_fork_left = &philo[0].mutex_fork_right;
		else
			philo[i].mutex_fork_left = &philo[i + 1].mutex_fork_right;
		philo[i].mutex_eat = &mutex_death_f->mutex_eat;
		philo[i].mutex_write = &mutex_death_f->mutex_write;
		philo[i].mutex_death = &mutex_death_f->mutex_death;
		philo[i].mutex_start = &mutex_death_f->mutex_start;
		if (pthread_create(&philo[i].thread, NULL, (void *)&routine, &philo[i]))
			return (-1);
		i++;
	}
	usleep(500);
	return (0);
}

int	init_data(t_philo philo[], t_mutex_and_death_f *mutex_death_f, char **arg)
{
	init_data_from_arg(philo, mutex_death_f, arg);
	if (init_data_mutex_and_thread(philo, mutex_death_f))
		return (-1);
	return (0);
}
