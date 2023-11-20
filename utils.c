#include "philo.h"

static t_bool	ft_did_die(t_data *data, t_philo *philo);
static t_bool	ft_did_eat(t_data *data, t_philo *philos);

/**
 * The ft_err function takes in a string and prints it to the standard
 * output, then exits the program with a return value of 1.
 *
 * @param err
 * @return int
 */
int	ft_err(char *err)
{
	printf("philo: %s\n", err);
	exit(1);
	return (1);
}

/**
 * The ft_atoi funtion converts the initial portion of the string
 * pointed to by str to int representation.
 *
 * @param str
 * @return int
 */
int	ft_atoi(char *str)
{
	int	s;
	int	n;

	s = 1;
	n = 0;
	if (*str == '-' || *str == '+')
		if (*str++ == '-')
			s *= -1;
	while (*str >= '0' && *str <= '9')
		n = n * 10 + *str++ - 48;
	return (n * s);
}

/**
 * The ft_wait_for_exit function waits for a philosopher to die or for
 * all philosophers to eat the maximum number of times.
 * 
 * @param data 
 * @param philos 
 */
void	ft_wait_for_exit(t_data *data, t_philo *philos)
{
	int	i;

	while (true)
	{
		i = -1;
		while (++i < data->philo_count)
		{
			if (ft_did_die(data, &philos[i]))
				return ;
			if (ft_did_eat(data, &philos[i]))
				return ;
		}
	}
}

/**
 * The ft_did_die function checks if a philosopher has died. If so, it
 * prints a message to the standard output and sets the is_game_over flag to
 * true.
 * 
 * @param data 
 * @param philo 
 * @return t_bool 
 */
static t_bool	ft_did_die(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&data->meal_mutex);
	if (ft_get_time_diff(philo->last_meal_time)
		> data->time_die_in_ms)
	{
		pthread_mutex_lock(&data->print_mutex);
		printf("[%dms] %d died\n",
			ft_get_rounded_time_diff(data->start_time, data->time_die_in_ms),
			philo->id);
		data->is_game_over = true;
		pthread_mutex_unlock(&data->print_mutex);
		pthread_mutex_unlock(&data->meal_mutex);
		return (true);
	}
	pthread_mutex_unlock(&data->meal_mutex);
	return (false);
}

/**
 * The ft_did_eat function checks if all philosophers have eaten the
 * maximum number of times. If so, it prints a message to the standard output
 * and sets the is_game_over flag to true.
 * 
 * @param data 
 * @param philos 
 * @return t_bool 
 */
static t_bool	ft_did_eat(t_data *data, t_philo *philos)
{
	int	i;
	int	have_all_eaten;

	i = -1;
	have_all_eaten = 0;
	pthread_mutex_lock(&data->meal_mutex);
	while (++i < data->philo_count && data->max_eat != -1)
	{
		if (philos[i].eat_count >= data->max_eat)
			have_all_eaten++;
	}
	if (have_all_eaten == data->philo_count)
	{
		pthread_mutex_lock(&data->print_mutex);
		printf("[%dms] all philosophers have eaten %d times\n",
			ft_get_rounded_time_diff(data->start_time, data->time_eat_in_ms),
			data->max_eat);
		data->is_game_over = true;
		pthread_mutex_unlock(&data->print_mutex);
		pthread_mutex_unlock(&data->meal_mutex);
		return (true);
	}
	pthread_mutex_unlock(&data->meal_mutex);
	return (false);
}
