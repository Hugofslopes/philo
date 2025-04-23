/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfilipe- <hfilipe-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:19:43 by hfilipe-          #+#    #+#             */
/*   Updated: 2025/04/23 11:04:57 by hfilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	actions2(t_p *philo)
{
	if (philo->ph_id % 2 == 1)
		execute_odds(&philo);
	else
		execute_even(&philo);
	if (philo->ph_id % 2 == 1)
	{
		while (1)
		{
			pthread_mutex_lock(&philo->ph->mutex[FRST_M]);
			if (philo->ph->fm_ate >= philo->ph->nbr_ph)
			{
				pthread_mutex_unlock(&philo->ph->mutex[FRST_M]);
				break ;
			}
			pthread_mutex_unlock(&philo->ph->mutex[FRST_M]);
			usleep(1000);
		}
	}
	meals_loop(&philo);
}

void	actions1(t_p *philo)
{
	while (1)
	{
		pthread_mutex_lock(&philo->ph->mutex[READY_TO_GOM]);
		if (philo->ph->ready_to_go)
		{
			pthread_mutex_unlock(&philo->ph->mutex[READY_TO_GOM]);
			break ;
		}
		pthread_mutex_unlock(&philo->ph->mutex[READY_TO_GOM]);
		usleep(1000);
	}
}

void	actions0(t_p *philo)
{
	while (1)
	{
		pthread_mutex_lock(&philo->ph->mutex[READY_M]);
		if (philo->ph->ready == philo->ph->nbr_ph)
		{
			pthread_mutex_unlock(&philo->ph->mutex[READY_M]);
			break ;
		}
		pthread_mutex_unlock(&philo->ph->mutex[READY_M]);
		usleep(1000);
	}
}

void	*actions(void *philosopher)
{
	t_p				*philo;

	philo = (t_p *)philosopher;
	pthread_mutex_lock(&philo->ph->mutex[READY_M]);
	philo->ph->ready++;
	pthread_mutex_unlock(&philo->ph->mutex[READY_M]);
	actions0(philo);
	actions1(philo);
	actions2(philo);
	return (NULL);
}
