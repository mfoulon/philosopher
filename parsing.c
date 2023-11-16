#include "philo.h"

int	parse_args(int argc, char **argv, t_p *p)
{
	if ((argc == 5 || argc == 6) && is_numeric(argv, 0, 1))
	{
		p->a.total = ft_atoi(argv[1]);
		p->a.die = ft_atoi(argv[2]);
		p->a.eat = ft_atoi(argv[3]);
		p->a.sleep = ft_atoi(argv[4]);
		p->a.m_eat = -1;
		if (argc == 6)
			p->a.m_eat = ft_atoi(argv[5]);
		if (p->a.total <= 0 || p->a.die <= 0 || p->a.eat <= 0 || p->a.sleep <= 0)
			return (0);
		return (1);
	}
	return (0);
}
