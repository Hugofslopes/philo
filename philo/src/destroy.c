#include "../includes/philosophers.h"

void	destroy(t_ph *ph)
{ 
	long	i;

	free(ph->fork);
    free(ph->threads);
	i = 0;
	while (i < ph->nbr_ph)
		mutex_destroy(&ph->fork[i++]);
}
