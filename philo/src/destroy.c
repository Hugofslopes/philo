/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfilipe- <hfilipe-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:27:03 by hfilipe-          #+#    #+#             */
/*   Updated: 2025/04/21 13:17:29 by hfilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	destroy(t_meal *ph)
{
	long	i;

	free(ph->threads);
	i = 0;
	while (i <= ph->nbr_ph - 1)
		pthread_mutex_destroy(&ph->fork[i++]);
	free(ph->fork);
	free(ph->philo);
	i = 0;
	while (i < NUM_MUTEXES)
		pthread_mutex_destroy(&ph->mutex[i++]);
}
