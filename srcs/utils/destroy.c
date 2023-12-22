#include "philo.h"

int	destroy_mutex(t_mutex_and_death_f *mutex_death_f)
{
	pthread_mutex_destroy(&mutex_death_f->mutex_death);
	pthread_mutex_destroy(&mutex_death_f->mutex_eat);
	pthread_mutex_destroy(&mutex_death_f->mutex_write);
	return (0);
}