#include "philo.h"
#include <pthread.h>

int death_checker2(t_p *p)
{
  pthread_mutex_lock(&p->a.dead);
  if (p->a.stop)
  {
    pthread_mutex_unlock(&p->a.dead);
    return (1); 
  }
  pthread_mutex_unlock(&p->a.dead);
  return (0);
}

void  stop(t_p *p)
{
  int   i;

  i = -1;
  while (!death_checker2(p))
    ft_usleep(1);
  while (i++ < p->a.total)
    pthread_join(p->ph[i].thread_id, NULL);
  pthread_mutex_destroy(&p->a.write_mutex);
  i = -1;
  while (++i < p->a.total)
    pthread_mutex_destroy(&p->ph[i].l_f);
  if (p->a.stop ==  2)
    printf("Each philosopher ate %d time(s)\n", p->a.m_eat);
  free(p->ph);
}

int main(int ac, char **av)
{
  t_p p;

  if (!(parse_args(ac, av, &p)))
    return (ft_exit("Invalid Args\n"));
  p.ph = malloc(sizeof(t_philo) * p.a.total);
  if (!p.ph)
    return (ft_exit("NULL Malloc\n"));
  if (!ft_init(&p) || !create_threads(&p))
  {
    free(p.ph);
    return (0);
  }
  stop(&p);
}
