#include "../includes/philosophers.h"

void	destroy(t_ph **ph)
{ 
	while ((*ph)->trh_nbr)
		pthread_mutex_destroy(&(*ph)->fork[(*ph)->trh_nbr--]);
}
