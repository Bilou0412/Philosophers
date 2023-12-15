#include "philo.h"

void	*func1(void *arg)
{
	int	i;

	(void)arg;
	i = -1;
	while (i++ < 10)
		printf("\033[95mthread 2:%d\033[0m\n", i);
	pthread_exit(NULL);
}

void	*func2(void *arg)
{
	int	i;

	(void)arg;
	i = -1;
	while (i++ < 10)
		printf("\033[91mthread 1:%d\033[0m\n", i);
	pthread_exit(NULL);
}

int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	pthread_t t1;
	pthread_t t2;

	pthread_create(&t1, NULL, func1, NULL);
	pthread_create(&t2, NULL, func2, NULL);
	usleep(500);
	return (0);
}