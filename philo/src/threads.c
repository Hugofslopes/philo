/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfilipe- <hfilipe-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:26:30 by hfilipe-          #+#    #+#             */
/*   Updated: 2025/03/22 14:42:41 by hfilipe-         ###   ########.fr       */
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
		if (!mutex_locked(*r_fk) && !mutex_locked(*l_fk) && !(*philo)->ph->is_dead)
			phil_eat(philo, l_fk, r_fk);
		else if (!(*philo)->ph->is_dead)
		{
			phil_sleep(philo);
			if (!mutex_locked(*r_fk) && !mutex_locked(*l_fk) && !(*philo)->ph->is_dead)
				phil_eat(philo, l_fk, r_fk);
			else	
				if ((*philo)->ph->tm_to_s > 0 && !(*philo)->ph->is_dead)
					phil_think(philo);
		}
	}
}

void	loop_without_meals(t_p **philo, t_mutex **r_fk, t_mutex **l_fk)
{
	while (!(*philo)->ph->is_dead)
	{
		if (!mutex_locked(*r_fk) && !mutex_locked(*l_fk) && !(*philo)->ph->is_dead)
		{
			phil_eat(philo, l_fk, r_fk);
			if (!(*philo)->ph->is_dead)
				phil_sleep(philo);
		}
		else if (!(*philo)->ph->is_dead)
		{
			if ((*philo)->ph->tm_to_s > 0 && !(*philo)->ph->is_dead)
					phil_think(philo);
			if (!(*philo)->ph->is_dead)
			{
				if (!mutex_locked(*r_fk) && !mutex_locked(*l_fk) && !(*philo)->ph->is_dead)
				{	
					phil_eat(philo, l_fk, r_fk);
					if (!(*philo)->ph->is_dead)
						phil_sleep(philo);
				}
			}
			else
				if (!(*philo)->ph->is_dead)
					phil_sleep(philo);	
		}
	}
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

void	*actions(void *philosopher)
{
	t_p		*philo;
	t_mutex	*l_fk;
	t_mutex	*r_fk;

	philo = (t_p *)philosopher;
	mutex_lock(&philo->ph->ready_m);
	philo->ph->ready += 1;
	mutex_unlock(&philo->ph->ready_m);
	wait_for_alltreads(&philo);
	r_fk = &philo->ph->fork[philo->ph_id];
	if (philo->ph_id == philo->ph->nbr_ph - 1)
		l_fk = &philo->ph->fork[0];
	else
		l_fk = &philo->ph->fork[philo->ph_id + 1];
	if (philo->ph_id % 2 == 0 || philo->ph_id == 0)
	{
		phil_eat(&philo, &l_fk, &r_fk);
		phil_sleep(&philo);
	}
	while (!all_odd_ate(&philo))
			;
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
