#include "philo.h"
#include <pthread.h>

void *is_dead(void *data)
{
  t_philo *ph;

  ph = (t_philo *)data;
  ft_usleep(ph->pa->die + 1);
  pthread_mutex_lock(&ph->pa->time_eat);
  pthread_mutex_lock(&ph->pa->finish);
  if (death_checker(0, ph) && !ph->finish && ((actual_time() - ph->ms_eat) \
    >- (long)(ph->pa->die)))
  {
    pthread_mutex_unlock(&ph->pa->time_eat);
    pthread_mutex_unlock(&ph->pa->finish);
    pthread_mutex_lock(&ph->pa->write_mutex);
    print_status("died\n", ph);
    pthread_mutex_unlock(&ph->pa->write_mutex);
    death_checker(1, ph);
  }
  pthread_mutex_unlock(&ph->pa->time_eat);
  pthread_mutex_unlock(&ph->pa->finish);
  return (NULL);
}

void  *thread(void *data)
{
  t_philo *ph;

  ph = (t_philo *)data;
  if (ph->id % 2 == 0)
    ft_usleep(ph->pa->eat / 10);
  while (!death_checker(0, ph))
  {
    pthread_create(&ph->thread_death_id, NULL, is_dead, data);
    eating(ph);
    pthread_detach(ph->thread_death_id);
    if ((int)++ph->nb_eat == ph->pa->m_eat)
    {
      pthread_mutex_lock(&ph->pa->finish);
      ph->finish = 1;
      ph->pa->nb_p_finish++;
      if (ph->pa->nb_p_finish == ph->pa->total)
      {
        pthread_mutex_unlock(&ph->pa->finish);
        death_checker(2, ph);
      }
      pthread_mutex_unlock(&ph->pa->finish);
      return (NULL);
    }
  }
  return (NULL);
}

int create_threads(t_p *p)
{
  int i;
  
  i = 0;
  while (i < p->a.total)
  {
    p->ph[i].pa = &p->a;
    if (pthread_create(&p->ph[i].thread_id, NULL, thread, &p->ph[i]) != 0)
      return (ft_exit("Pthread did not return 0\n"));
    i++;
  }
  return (1);
}
