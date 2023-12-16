#include "philo.h"

int	main(int argc, char **argv)
{
	t_philo philo[200];
	int i;

	i = 0;
	if (argc < 5 || argc > 6 || invalid_arg(argv))
		return (printf("Program take the following arguments:\n number_of_philosophers : [MIN 1 ; MAX 200]\n time_to_die : MIN 1 \n time_to_eat : MIN 1\n time_to_sleep : MIN 1\n [number_of_times_each_philosopher_must_eat]\n"),
			0);
	init_data(philo, argv);
	while (i < ft_atoi(argv[1]))
	{
		printf("id : %d\n%d\n%d\n%d\n%d\n%d\n", philo[i].id,philo[i].number_of_philosophers,
			philo[i].time_to_die, philo[i].time_to_eat, philo[i].time_to_sleep,
			philo[i].number_of_times_each_philosopher_must_eat);
		i++;
	}
	return (0);
}