#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_arg
{
    int						total;
    int						die;
    int						eat;
    int						sleep;
    int						m_eat;
    long int				start_t;
    pthread_mutex_t			write_mutex;
    pthread_mutex_t			dead;
    pthread_mutex_t			time_eat;
    pthread_mutex_t			finish;
    int						nb_p_finish;
    int						stop;
}							t_arg;

typedef struct s_philo
{
    int						id;
    pthread_t				thread_id;
    pthread_t				thread_death_id;
    pthread_mutex_t			*r_f;
    pthread_mutex_t			l_f;
    t_arg					*pa;
    long int				ms_eat;
    unsigned int			nb_eat;
    int						finish;
}							t_philo;

typedef struct s_p
{
    t_philo					*ph;
    t_arg					a;
}							t_p;

//----------------------- philo_utils.c -------------//

int 	is_numeric(char **argv, int i, int j);
int 	ft_exit(char *str);
long int	actual_time(void);
void	ft_usleep(long int time_in_ms);
int   death_checker(int i, t_philo *ph);

//----------------------- libft_utils.c -------------//

void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(long int ln, int fd);
int 	ft_strlen(char *str);
int	  ft_atoi(const char *str);

//----------------------- parsing.c -----------------//
int   parse_args(int argc, char **argv, t_p *p);

//----------------------- init.c -----------------//
void	init_mutex(t_p *p);
int   ft_init(t_p *p);

//----------------------- actions.c -----------------//
void  eating(t_philo *ph);
void  sleep_think(t_philo *ph);
void  print_status(char *s, t_philo *ph);

//----------------------- threads.c -----------------//
void *is_dead(void *data);
void  *thread(void *data);
int create_threads(t_p *p);

#endif
