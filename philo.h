#ifndef PHILO_H
# define PHILO_H

# define EARGS "error: invalid arguments\nusage: ./philo [nb] [t2-die] [t2-eat] [t2-sleep] [nb-t2-eat]"
# define EUNKN "error: malloc probably failed"
# define ETHRD "error: thread error"

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

typedef enum e_bool
{
	false,
	true
}	t_bool;

typedef struct timeval	t_timeval;

typedef struct s_data
{
	int				philo_count;
	int				time_die_in_ms;
	int				time_eat_in_ms;
	int				time_sleep_in_ms;
	int				max_eat;
	unsigned long	start_time;
	t_bool			is_ready;
	t_bool			is_game_over;
	pthread_mutex_t	data_mutex;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	print_mutex;
}	t_data;

typedef struct s_philo
{
	int				id;
	int				eat_count;
	unsigned long	last_meal_time;
	t_data			*data;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}	t_philo;

// ------------ FILES ------------- //

// actions.c
void	*ft_single_philo(void *arg);
void	*ft_multiple_philos(void *arg);
void	ft_print(t_philo *philo, char *msg, int arg_ms);
void	ft_eat(t_philo *philo);
void	ft_sleep_and_think(t_philo *philo);

// utils.c
int	ft_err(char *err);
int	ft_atoi(char *str);
void	ft_wait_for_exit(t_data *data, t_philo *philos);

// parse.c
t_bool	ft_parse_args(int argc, char **argv, t_data *data);

// actions.c
void	ft_init_philos(t_philo *philos, t_data *data, pthread_mutex_t *forks);
void	ft_init_data(t_data *data);

// threading.c
t_bool	ft_spawn_threads(t_data *data, t_philo *philos);

// time.c
unsigned long	ft_get_time_in_ms(void);
int	ft_get_time_diff(unsigned long time);
int	ft_get_rounded_time_diff(unsigned long time, int round);
void	ft_usleep(unsigned long time);

#endif
