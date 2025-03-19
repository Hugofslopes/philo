#include "../includes/philosophers.h"

int	unlocked_mutex(pthread_mutex_t *id)
{
	if (pthread_mutex_lock(id) == 0)
	{
		pthread_mutex_unlock(id);
			return (1);
	}
	return (0);
}

void	*actions(void *philosopher)
{
	t_p				*philo;
	pthread_mutex_t	l_fk;
    pthread_mutex_t	r_fk;
	
	philo = (t_p *)philosopher;
	r_fk = philo->ph->fork[philo->ph_id];
	if (philo->ph_id == philo->ph->nbr_ph - 1)
		l_fk = philo->ph->fork[0];
	else
		l_fk = philo->ph->fork[philo->ph_id + 1];
	if (unlocked_mutex(&r_fk) && unlocked_mutex(&l_fk))
	{
		pthread_mutex_lock(&r_fk);
		printf("%lld %d has taken a fork\n", curr_tm() - philo->ph->st_time, philo->ph_id);
		pthread_mutex_lock(&l_fk);
		printf("%lld %d is eating\n", curr_tm() - philo->ph->st_time, philo->ph_id);
		usleep(philo->ph->tm_to_e * 999);
		pthread_mutex_unlock(&r_fk);
		pthread_mutex_unlock(&l_fk);
		philo->last_meal = curr_tm();
	}
	printf("%lld %d is sleeping\n",curr_tm() -  philo->ph->st_time, philo->ph_id);
	usleep(philo->ph->tm_to_s * 999);
	if (philo->ph->tm_to_s > 0)
	{
		printf("%lld %d is thinking\n", curr_tm() - philo->ph->st_time, philo->ph_id);
		usleep(philo->ph->tm_to_s * 999);
	}
	return (NULL);
}

void wait_for_threads(t_ph **ph)
{
	long	i;

	i = 0;
	while (i < (*ph)->nbr_ph)
	{
		if (curr_tm() - (*ph)->philo[i].last_meal  > (*ph)->tm_to_d)
		{
			printf("%lld %d died\n", curr_tm() - (*ph)->st_time, (*ph)->philo[i].ph_id);
			(*ph)->is_dead = 1;
			break ;
		}
		pthread_join((*ph)->threads[i], NULL);
		i++;
	}
}

void manage_threads(t_ph **ph)
{ 
	if ((*ph)->nr_meals && !(*ph)->is_dead)
	{
		while ((*ph)->nr_meals && !(*ph)->is_dead)
		{
			wait_for_threads(ph);
			(*ph)->nr_meals--;
		}
	}
	else
		while (!(*ph)->is_dead)
			wait_for_threads(ph);
}
