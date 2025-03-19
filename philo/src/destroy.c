#include "../includes/philosophers.h"

void	destroy(t_ph *ph)
{ 
	long	i;

	free(ph->fork);
    free(ph->threads); 
    free(ph->philo);
	i = 0;
	while (i < ph->nbr_ph)
		pthread_mutex_destroy(&ph->fork[i++]);
}
