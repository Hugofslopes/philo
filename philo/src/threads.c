/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfilipe- <hfilipe-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:26:30 by hfilipe-          #+#    #+#             */
/*   Updated: 2025/04/14 15:24:33 by hfilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	meals_loop2(t_p **philo)
{
	pthread_mutex_lock(&(*philo)->ph->finished);
	if (!(*philo)->ph->m_finished)
	{
		pthread_mutex_unlock(&(*philo)->ph->finished);
		phil_think(philo);
	}
	else
		return (pthread_mutex_unlock(&(*philo)->ph->finished), 1);
	return (0);
}

int	meals_loop(t_p **philo)
{
	pthread_mutex_lock(&(*philo)->ph->finished);
	while (!(*philo)->ph->m_finished)
	{
		if (!mutex_locked((*philo)->r_fk) && !mutex_locked((*philo)->l_fk) && \
		!(*philo)->ph->m_finished)
		{
			pthread_mutex_unlock(&(*philo)->ph->finished);
			phil_eat(philo);
			pthread_mutex_lock(&(*philo)->ph->finished);
			if (!(*philo)->ph->m_finished)
			{
				pthread_mutex_unlock(&(*philo)->ph->finished);
				phil_sleep(philo);
			}
			else
				return (pthread_mutex_unlock(&(*philo)->ph->finished));
			if (meals_loop2(philo))
				return (0);
			pthread_mutex_lock(&(*philo)->ph->finished);
			if ((*philo)->ph->m_finished)
				return (pthread_mutex_unlock(&(*philo)->ph->finished));
		}
	}
	return (pthread_mutex_unlock(&(*philo)->ph->finished));
}

void	manage_threads(t_meal *meal)
{
	long	i;

	i = 0;
	while (i < meal->nbr_ph)
	{
		if (i == 0)
			pthread_join(meal->supervisor, NULL);
		pthread_join(meal->threads[i], NULL);
		i++;
	}
}
