#ifndef PHILO_H
# define PHILO_H

# include <ctype.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef struct s_philo
{
	pthread_t	thread;
	int			id;
	int			number_of_philosophers;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			number_of_times_each_philosopher_must_eat;
}				t_philo;

/*----------------check_arg.c-----------------*/

bool			invalid_arg(char **arg);

/*----------------utils-----------------------*/

int				ft_atoi(const char *str);
bool			ft_isdigit(int c);
void			init_data(t_philo philo[], char **arg);

#endif