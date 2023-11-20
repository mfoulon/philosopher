#include "philo.h"

int	main(int argc, char *argv[])
{
	t_data			data;
	t_philo			*philos;
	pthread_mutex_t	*forks;

	ft_init_data(&data);
	if (!ft_parse_args(argc, argv, &data))
		return (ft_err(EARGS));
	forks = malloc(sizeof(pthread_mutex_t) * data.philo_count);
	if (!forks)
		return (ft_err(EUNKN), 1);
	philos = malloc(sizeof(t_philo) * data.philo_count);
	if (!philos)
		return (ft_err(EUNKN), 1);
	ft_init_philos(philos, &data, forks);
	if (!ft_spawn_threads(&data, philos))
		return (ft_err(ETHRD));
	free(forks);
	return (0);
}
