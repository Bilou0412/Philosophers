#ifndef PHILO_H
# define PHILO_H

# include <ctype.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

/*----------------struct-----------------*/

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				number_of_philosophers;
	int				nb_eat;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			number_of_times_each_philosopher_must_eat;
	size_t			start;
	size_t			last_eating;
	pthread_mutex_t	mutex_fork_left;
	pthread_mutex_t	*mutex_fork_right;
	pthread_mutex_t	*mutex_death;
	pthread_mutex_t	*mutex_eat;
	pthread_mutex_t	*mutex_write;
	bool			*death;
}					t_philo;

typedef struct s_mutex_and_death_f
{
	pthread_mutex_t	mutex_death;
	pthread_mutex_t	mutex_eat;
	pthread_mutex_t	mutex_write;
	bool			death;
}					t_mutex_and_death_f;
/*----------------check_arg.c-----------------*/

bool				invalid_arg(char **arg);
/*----------------utils-----------------------*/

int					ft_atoi(const char *str);
int					init_data(t_philo philo[],
						t_mutex_and_death_f *mutex_death_f, char **arg);
bool				ft_isdigit(int c);
size_t				get_current_time(void);
int					ft_usleep(size_t milliseconds, t_philo *philo);
/*----------------action.c-----------------------*/

void				philo_write(t_philo *philo, char *str);
void				fork_right(t_philo *philo);
void				fork_left(t_philo *philo);
void				philo_death(t_philo *philo);
void				philo_sleep(t_philo *philo);
void				philo_eat(t_philo *philo);
void				philo_eat_odd(t_philo *philo);

/*----------------main.c-----------------------*/

void				*routine(void *philo);
#endif