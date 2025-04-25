/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfilipe- <hfilipe-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 09:41:58 by hfilipe-          #+#    #+#             */
/*   Updated: 2025/04/25 11:41:46 by hfilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	phil_died(t_p *philo)
{
	pthread_mutex_lock(&philo->ph->mutex[FINISHED]);
	philo->ph->m_finished = 1;
	pthread_mutex_unlock(&philo->ph->mutex[FINISHED]);
	pthread_mutex_lock(&philo->ph->mutex[CRR_TM]);
	printf("%ld %d died\n", (curr_tm() - philo->st_time) \
	, philo->ph_id + 1);
	pthread_mutex_unlock(&philo->ph->mutex[CRR_TM]);
}

void	check_all_ate(t_meal *meal, t_p *phi)
{
	long	i;
	long	count;

	i = 0;
	count = 0;
	while (i <= meal->nbr_ph - 1)
	{
		pthread_mutex_lock(&meal->mutex[MEALS_ATE]);
		if (phi[i].meals_ate >= phi[i].nr_meals)
			count++;
		pthread_mutex_unlock(&meal->mutex[MEALS_ATE]);
		i++;
	}
	if (count == meal->nbr_ph)
	{
		pthread_mutex_lock(&meal->mutex[FINISHED]);
		meal->m_finished = 1;
		pthread_mutex_unlock(&meal->mutex[FINISHED]);
	}
}

void	monitoring1(t_meal *meal, t_p *phi, int nr_m)
{
	long	i;

	i = 0;
	while (!meal->m_finished)
	{
		while (i < meal->nbr_ph && !meal->m_finished)
		{
			pthread_mutex_lock(&phi->ph->mutex[CRR_TM]);
			if (curr_tm() - phi[i].last_meal >= phi[i].tm_to_d)
			{
				pthread_mutex_unlock(&phi->ph->mutex[CRR_TM]);
				phil_died(&phi[i]);
				break ;
			}
			pthread_mutex_unlock(&phi->ph->mutex[CRR_TM]);
			if (nr_m)
				check_all_ate(meal, phi);
			i++;
		}
		usleep(1000);
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
		pthread_mutex_lock(&meal->mutex[READY_TO_GOM]);
		if (meal->ready_to_go)
		{
			pthread_mutex_unlock(&meal->mutex[READY_TO_GOM]);
			break ;
		}
		pthread_mutex_unlock(&meal->mutex[READY_TO_GOM]);
		usleep(100);
	}
	phi = meal->philo;
	if (meal->nr_meals > 0)
		monitoring1(meal, phi, 1);
	else
		monitoring1(meal, phi, 0);
	return (NULL);
}
