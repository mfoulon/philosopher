#include "philo.h"

void	init_mutex(t_p *p)
{
	pthread_mutex_init(&p->a.write_mutex, NULL);
	pthread_mutex_init(&p->a.dead, NULL);
	pthread_mutex_init(&p->a.time_eat, NULL);
	pthread_mutex_init(&p->a.finish, NULL);
}

int ft_init(t_p *p)
{
  int  i;

  i = 0;
  p->a.start_t = actual_time();
  p->a.stop = 0;
  p->a.nb_p_finish = 0;
  init_mutex(p);
  while (i < p->a.total)
  {
    p->ph[i].id = i + 1;
    p->ph[i].ms_eat = p->a.start_t;
    p->ph[i].nb_eat = 0; 
    p->ph[i].finish = 0; 
    p->ph[i].r_f = NULL;
    pthread_mutex_init(&p->ph[i].l_f, NULL);
    if (p->a.total == 1)
      return (1);
    if (i == p->a.total - 1)
      p->ph[i].r_f = &p->ph[0].l_f;
    else
      p->ph[i].r_f = &p->ph[i + 1].l_f;
    i++;
  }
  return (1);
}
