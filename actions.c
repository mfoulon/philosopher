#include "philo.h"

void  print_status(char *s, t_philo *ph)
{
  long int time;

  time = -1;
  time = actual_time() - ph->pa->start_t;
  if (time >= 0 && time <= 2147483647 && !death_checker(0, ph))
  {
		printf("%ld ", time);
		printf("Philo %d %s", ph->id, s);
	}
    // printf("%ld Philo %d %s", time, ph->id, s);
}

void  sleep_think(t_philo *ph)
{
  pthread_mutex_lock(&ph->pa->write_mutex);
  print_status("is sleeping\n", ph);
  pthread_mutex_unlock(&ph->pa->write_mutex);
  ft_usleep(ph->pa->sleep);
  pthread_mutex_lock(&ph->pa->write_mutex);
  print_status("is thinking\n", ph);
  pthread_mutex_unlock(&ph->pa->write_mutex);
}

void  eating(t_philo *ph)
{
  pthread_mutex_lock(&ph->l_f);
  pthread_mutex_lock(&ph->pa->write_mutex);
  print_status("has taken a fork\n", ph);
  pthread_mutex_unlock(&ph->pa->write_mutex);
  if (!ph->r_f)
  {
    ft_usleep(ph->pa->die * 2);
    return ;
  }
  pthread_mutex_lock(ph->r_f);
  pthread_mutex_lock(&ph->pa->write_mutex);
  print_status("has taken a fork\n", ph);
  pthread_mutex_unlock(&ph->pa->write_mutex);
  pthread_mutex_lock(&ph->pa->write_mutex);
  print_status("is eating\n", ph);
  pthread_mutex_lock(&ph->pa->time_eat);
  ph->ms_eat = actual_time();
  pthread_mutex_unlock(&ph->pa->time_eat);
  pthread_mutex_unlock(&ph->pa->write_mutex);
  ft_usleep(ph->pa->eat);
  pthread_mutex_unlock(ph->r_f);
  pthread_mutex_unlock(&ph->l_f);
  sleep_think(ph);
}
