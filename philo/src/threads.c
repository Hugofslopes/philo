#include "../includes/philosophers.h"

void	*thread_function(void *ph)
{
	t_ph			*phi;
	pthread_mutex_t	fork;
	long			*tm_to_e;
	
	phi = (t_ph *)ph;
    fork = phi->fork[0];
	tm_to_e = *(phi->tm_to_e);
	pthread_mutex_lock(&fork);
	usleep(*tm_to_e);
	pthread_mutex_unlock(&fork);
	return (NULL);
}


void manage_threads()
{
	thread 1
	timestamp_in_ms X has taken a fork 
	usleep(time to eat);
	timestamp_in_ms X is eating

	timestamp_in_ms X is sleeping
	usleep(time to eat);
	verificar se morre ( tempo viver < tempo dormiu)
	timestamp_in_ms X is thinking
	tempo de morrer - tempo dormir 
	timestamp_in_ms X died
	
}