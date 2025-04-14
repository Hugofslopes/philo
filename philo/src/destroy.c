/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfilipe- <hfilipe-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:27:03 by hfilipe-          #+#    #+#             */
/*   Updated: 2025/04/14 15:06:55 by hfilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	destroy(t_meal *ph)
{
	long	i;

	usleep(100);
	free(ph->threads);
	i = 0;
	while (i <= ph->nbr_ph - 1)
		pthread_mutex_destroy(&ph->fork[i++]);
	free(ph->fork);
	free(ph->philo);
	pthread_mutex_destroy(&ph->ready_m);
	pthread_mutex_destroy(&ph->first_meal);
	pthread_mutex_destroy(&ph->finished);
	pthread_mutex_destroy(&ph->crr_tm);
	pthread_mutex_destroy(&ph->ready_to_gom);
}
