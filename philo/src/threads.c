/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfilipe- <hfilipe-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:26:30 by hfilipe-          #+#    #+#             */
/*   Updated: 2025/04/25 11:41:48 by hfilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	meals_loop2(t_p **philo)
{
	pthread_mutex_lock(&(*philo)->ph->mutex[FINISHED]);
	if (!(*philo)->ph->m_finished)
	{
		pthread_mutex_unlock(&(*philo)->ph->mutex[FINISHED]);
		phil_sleep(philo);
	}
	else
		return (pthread_mutex_unlock(&(*philo)->ph->mutex[FINISHED]), 1);
	pthread_mutex_lock(&(*philo)->ph->mutex[FINISHED]);
	if (!(*philo)->ph->m_finished)
	{
		pthread_mutex_unlock(&(*philo)->ph->mutex[FINISHED]);
		phil_think(philo);
	}
	else
		return (pthread_mutex_unlock(&(*philo)->ph->mutex[FINISHED]), 1);
	return (0);
}

int	meals_loop(t_p **philo)
{
	pthread_mutex_lock(&(*philo)->ph->mutex[FINISHED]);
	while (!(*philo)->ph->m_finished)
	{
		pthread_mutex_unlock(&(*philo)->ph->mutex[FINISHED]);
		if (!mutex_locked((*philo)->r_fk) && !mutex_locked((*philo)->l_fk))
		{
			pthread_mutex_lock(&(*philo)->ph->mutex[FINISHED]);
			if (!(*philo)->ph->m_finished)
			{
				pthread_mutex_unlock(&(*philo)->ph->mutex[FINISHED]);
				phil_eat(philo);
			}
			else
				return (pthread_mutex_unlock(&(*philo)->ph->mutex[FINISHED]));
			if (meals_loop2(philo))
				return (0);
		}
		usleep(100);
		pthread_mutex_lock(&(*philo)->ph->mutex[FINISHED]);
	}
	return (pthread_mutex_unlock(&(*philo)->ph->mutex[FINISHED]));
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
