/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfilipe- <hfilipe-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 15:10:27 by hfilipe-          #+#    #+#             */
/*   Updated: 2025/04/23 11:22:29 by hfilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	execute_even(t_p **philo)
{
	pthread_mutex_lock(&(*philo)->ph->mutex[FRST_M]);
	(*philo)->ph->fm_ate++;
	pthread_mutex_unlock(&(*philo)->ph->mutex[FRST_M]);
	phil_think(philo);
}

void	execute_odds(t_p **philo)
{
	phil_eat(philo);
	pthread_mutex_lock(&(*philo)->ph->mutex[FINISHED]);
	if (!(*philo)->ph->m_finished)
	{
		pthread_mutex_unlock(&(*philo)->ph->mutex[FINISHED]);
		phil_sleep(philo);
		return ;
	}
	pthread_mutex_unlock(&(*philo)->ph->mutex[FINISHED]);
}

void	one_philo(t_meal **ph)
{
	printf("%d %d has taken a fork\n", 0, 0);
	usleep((*ph)->tm_to_d * 1000);
	printf("%ld %d died\n", (*ph)->tm_to_d, 0);
}
