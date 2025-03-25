/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfilipe- <hfilipe-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 09:41:58 by hfilipe-          #+#    #+#             */
/*   Updated: 2025/03/25 19:57:28 by hfilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	all_ready(t_ph **ph)
{
	if ((*ph)->ready == (*ph)->nbr_ph)
		return (1);
	return (0);
}

void	monitoring2(t_ph *philos, t_p **phi)
{
	long	i;

	while (!philos->is_dead)
	{
		i = 0;
		phi = phi + i ;
		while (i < philos->nbr_ph - 1 && !philos->is_dead)
		{
			if (curr_tm() - (*phi)->last_meal > philos->tm_to_d)
				phil_died(phi);
			i++;
		}
	}
}

void	monitoring1(t_ph *philos, t_p **phi)
{
	long	i;
	t_p		*phi2;

	phi2 = *phi + (philos->nbr_ph - 1);
	while (!philos->is_dead && philos->nr_meals < phi2->nr_meals)
	{
		i = 0;
		phi = phi + i ;
		while (i < philos->nbr_ph - 1 && !philos->is_dead && \
			philos->nr_meals < (*phi)->nr_meals)
		{
			if (curr_tm() - (*phi)->last_meal > philos->tm_to_d)
				phil_died(phi);
			i++;
		}
	}
}

void	*monitoring(void *ph)
{
	t_ph	*philos;
	t_p		**phi;

	philos = (t_ph *)ph;
	while (!all_ready(&philos))
		;
	phi = &philos->philo;
	if (philos->nr_meals > 0)
		monitoring1(philos, phi);
	else
		monitoring2(philos, phi);
	return (NULL);
}
