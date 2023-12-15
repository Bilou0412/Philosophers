#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef struct s_philo
{
	pthread_mutex_t	mutex;
	pthread_mutex_t	mutex1;
	int				nb;
}					t_philo;

#endif