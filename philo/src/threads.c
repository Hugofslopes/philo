/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfilipe- <hfilipe-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:26:30 by hfilipe-          #+#    #+#             */
/*   Updated: 2025/03/21 18:26:04 by hfilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	wait_for_alltreads(t_p **phi)
{
	while (mutex_locked(&(*phi)->ph->wait_to_start))
		;
}

void	loop_with_nr_meals(t_p **philo, t_mutex **l_fk, t_mutex **r_fk)
{
	while (!(*philo)->ph->is_dead && (*philo)->nr_meals \
	< (*philo)->ph->nr_meals)
	{
		if (!mutex_locked(*r_fk) && !mutex_locked(*l_fk))
			phil_eat(philo, l_fk, r_fk);
		phil_sleep(philo);
		if ((*philo)->ph->tm_to_s > 0)
			phil_think(philo);
		if (curr_tm() - (*philo)->last_meal > (*philo)->ph->tm_to_d)
			phil_died(philo);
	}
}

void	loop_without_meals(t_p **philo, t_mutex **r_fk, t_mutex **l_fk)
{
	while (!(*philo)->ph->is_dead)
	{
		if (!mutex_locked(*r_fk) && !mutex_locked(*l_fk))
			phil_eat(philo, l_fk, r_fk);
		phil_sleep(philo);
		if ((*philo)->ph->tm_to_s > 0)
			phil_think(philo);
		if (curr_tm() - (*philo)->last_meal > (*philo)->ph->tm_to_d)
			phil_died(philo);
	}
}

void	*actions(void *philosopher)
{
	t_p		*philo;
	t_mutex	*l_fk;
	t_mutex	*r_fk;

	philo = (t_p *)philosopher;
	wait_for_alltreads(&philo);
	philo->ph->ready += 1;
	r_fk = &philo->ph->fork[philo->ph_id];
	if (philo->ph_id == philo->ph->nbr_ph - 1)
		l_fk = &philo->ph->fork[0];
	else
		l_fk = &philo->ph->fork[philo->ph_id + 1];
	if (philo->ph->nr_meals > 0)
		loop_with_nr_meals(&philo, &r_fk, &l_fk);
	else
		loop_without_meals(&philo, &r_fk, &l_fk);
	return (NULL);
}

void	manage_threads(t_ph *ph)
{
	long	i;

	i = 0;
	while (i < ph->nbr_ph)
	{
		pthread_join(ph->threads[i], NULL);
		i++;
	}
}
