/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfilipe- <hfilipe-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 15:10:27 by hfilipe-          #+#    #+#             */
/*   Updated: 2025/04/14 16:11:11 by hfilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	execute_even(t_p **philo)
{
	pthread_mutex_lock(&(*philo)->ph->first_meal);
	(*philo)->ph->odd_ate++;
	pthread_mutex_unlock(&(*philo)->ph->first_meal);
	phil_think(philo);
}

void	execute_odds(t_p **philo)
{
	phil_eat(philo);
	pthread_mutex_lock(&(*philo)->ph->finished);
	if (!(*philo)->ph->m_finished)
	{
		pthread_mutex_unlock(&(*philo)->ph->finished);
		phil_sleep(philo);
		return ;
	}
	pthread_mutex_unlock(&(*philo)->ph->finished);
}

int	count_odd_phil(int x)
{
	int		count;
	long	i;

	count = 0;
	i = 0;
	while (i <= x - 1)
	{
		if (i % 2 != 0)
			count++;
		i++;
	}
	return (count);
}

int	all_odd_ate(t_p **philo)
{
	if ((*philo)->ph->odd_ate >= count_odd_phil((*philo)->ph->nbr_ph))
		return (1);
	return (0);
}

void	one_philo(t_meal **ph)
{
	printf("%d %d has taken a fork\n", 0, 0);
	usleep((*ph)->tm_to_d * 1000);
	printf("%ld %d died\n", (*ph)->tm_to_d, 0);
}
