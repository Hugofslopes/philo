/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfilipe- <hfilipe-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:19:43 by hfilipe-          #+#    #+#             */
/*   Updated: 2025/04/14 15:39:46 by hfilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	actions2(t_p *philo)
{
	if (philo->ph_id % 2 == 1)
		execute_odds(&philo);
	else
		execute_even(&philo);
	while (1)
	{
		pthread_mutex_lock(&philo->ph->first_meal);
		if (philo->ph->odd_ate >= philo->ph->odd_ph)
		{
			pthread_mutex_unlock(&philo->ph->first_meal);
			break ;
		}
		pthread_mutex_unlock(&philo->ph->first_meal);
		usleep(1000);
	}
	meals_loop(&philo);
}

void	actions1(t_p *philo)
{
	while (1)
	{
		pthread_mutex_lock(&philo->ph->ready_to_gom);
		if (philo->ph->ready_to_go)
		{
			pthread_mutex_unlock(&philo->ph->ready_to_gom);
			break ;
		}
		pthread_mutex_unlock(&philo->ph->ready_to_gom);
		usleep(1000);
	}
}

void	actions0(t_p *philo)
{
	while (1)
	{
		pthread_mutex_lock(&philo->ph->ready_m);
		if (philo->ph->ready == philo->ph->nbr_ph)
		{
			pthread_mutex_unlock(&philo->ph->ready_m);
			break ;
		}
		pthread_mutex_unlock(&philo->ph->ready_m);
		usleep(1000);
	}
}

void	*actions(void *philosopher)
{
	t_p				*philo;

	philo = (t_p *)philosopher;
	pthread_mutex_lock(&philo->ph->ready_m);
	philo->ph->ready++;
	pthread_mutex_unlock(&philo->ph->ready_m);
	actions0(philo);
	actions1(philo);
	actions2(philo);
	return (NULL);
}
