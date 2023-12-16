#include "philo.h"

void	*func1(void *philo)
{
	char	*ret;
	t_philo	*tmp_philo;

	tmp_philo = (t_philo *)philo;
	ret = strdup("ret 1");
	pthread_mutex_lock(&(tmp_philo->mutex));
	while (tmp_philo->nb < 10)
		printf("\033[95mthread 1:%d\033[0m\n", tmp_philo->nb++);
	pthread_mutex_unlock(&(tmp_philo->mutex));
	return (ret);
}

void	*func2(void *philo)
{
	char	*ret;
	t_philo	*tmp_philo;

	tmp_philo = (t_philo *)philo;
	ret = strdup("ret 2");
	pthread_mutex_lock(&(tmp_philo->mutex));
	while (tmp_philo->nb < 20 && tmp_philo->nb > 9)
		printf("\033[91mthread 2:%d\033[0m\n", tmp_philo->nb++);
	pthread_mutex_unlock(&(tmp_philo->mutex));
	return (ret);
}

int	main(int argc, char **argv)
{
	if (argc < 5 || argc > 6 || invalid_arg(argv))
		return (printf("Program take the following arguments:\n number_of_philosophers : [MIN 1 ; MAX 200]\n time_to_die : MIN 1 \n time_to_eat : MIN 1\n time_to_sleep : MIN 1\n [number_of_times_each_philosopher_must_eat]\n"),
			0);
	(void)argv;
	pthread_t t1;
	pthread_t t2;
	t_philo philo;
	char *str1;
	char *str2;

	philo.nb = 0;
	pthread_mutex_init(&(philo.mutex), NULL);
	pthread_mutex_init(&(philo.mutex1), NULL);
	if (pthread_create(&t1, NULL, func1, &philo) || pthread_create(&t2, NULL,
			func2, &philo))
		return (1);
	if (pthread_join(t1, (void **)&str1) || pthread_join(t2, (void **)&str2))
		return (1);
	printf("string 1: %s\n", str1);
	printf("string 2: %s\n", str2);
	pthread_mutex_destroy(&(philo.mutex));
	pthread_mutex_destroy(&(philo.mutex1));
	free(str1);
	free(str2);
	return (0);
}