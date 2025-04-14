/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfilipe- <hfilipe-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 09:41:58 by hfilipe-          #+#    #+#             */
/*   Updated: 2025/04/14 16:26:33 by hfilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	check_all_ate(t_meal *meal, t_p *phi)
{
	long	i;
	long	count;

	i = 0;
	count = 0;
	while (i <= meal->nbr_ph - 1)
	{
		pthread_mutex_lock(&meal->meals_ate);
		if (phi[i].meals_ate == phi[i].nr_meals)
			count++;
		pthread_mutex_unlock(&meal->meals_ate);
		i++;
	}
	if (count == meal->nbr_ph)
	{
		pthread_mutex_lock(&meal->finished);
		meal->m_finished = 1;
		pthread_mutex_unlock(&meal->finished);
	}
}

void	monitoring1(t_meal *meal, t_p *phi, int nr_m)
{
	long	i;

	i = 0;
	while (!meal->m_finished)
	{
		while (i < meal->nbr_ph - 1 && !meal->m_finished)
		{
			pthread_mutex_lock(&phi->ph->crr_tm);
			if (curr_tm() - phi[i].last_meal - 5 > phi[i].tm_to_d)
			{
				pthread_mutex_unlock(&phi->ph->crr_tm);
				phil_died(&phi[i]);
				break ;
			}
			pthread_mutex_unlock(&phi->ph->crr_tm);
			if (nr_m)
				check_all_ate(meal, phi);
			i++;
		}
		i = 0;
	}
}

void	*monitoring(void *meals)
{
	t_meal	*meal;
	t_p		*phi;

	meal = (t_meal *)meals;
	while (1)
	{
		pthread_mutex_lock(&meal->ready_to_gom);
		if (meal->ready_to_go)
		{
			pthread_mutex_unlock(&meal->ready_to_gom);
			break ;
		}
		pthread_mutex_unlock(&meal->ready_to_gom);
		usleep(100);
	}
	phi = meal->philo;
	if (meal->nr_meals > 0)
		monitoring1(meal, phi, 1);
	else
		monitoring1(meal, phi, 0);
	return (NULL);
}
