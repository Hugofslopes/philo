/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfilipe- <hfilipe-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:26:50 by hfilipe-          #+#    #+#             */
/*   Updated: 2025/03/25 16:23:06 by hfilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	phil_eat(t_p **philo, t_mutex **l_fk, t_mutex **r_fk)
{
	mutex_lock(*r_fk);
	printf("%ld %d has taken a fork\n", (curr_tm() - (*philo)->ph->st_time) \
	, (*philo)->ph_id + 1);
	mutex_lock(&(*philo)->ph->first_meal);
	(*philo)->ph->odd_ate++;
	mutex_unlock(&(*philo)->ph->first_meal);
	mutex_lock(*l_fk);
	printf("%ld %d has taken a fork\n", (curr_tm() - (*philo)->ph->st_time) \
	, (*philo)->ph_id + 1);
	(*philo)->last_meal = curr_tm();
	printf("%ld %d is eating\n", (curr_tm() - (*philo)->ph->st_time), \
	(*philo)->ph_id + 1);
	usleep((*philo)->ph->tm_to_e * 1000);
	mutex_unlock(*r_fk);
	mutex_unlock(*l_fk);
	(*philo)->nr_meals++;
}

void	phil_sleep(t_p **philo)
{
	printf("%ld %d is sleeping\n", (curr_tm() - (*philo)->ph->st_time) \
	, (*philo)->ph_id + 1);
	usleep((*philo)->ph->tm_to_s * 1000);
}

void	phil_think(t_p **philo)
{
	printf("%ld %d is thinking\n", (curr_tm() - (*philo)->ph->st_time) \
	, (*philo)->ph_id + 1);
	usleep((*philo)->ph->tm_to_tk * 1000);
}

void	phil_died(t_p **philo)
{
	printf("%ld %d died\n", (curr_tm() - (*philo)->ph->st_time) \
	, (*philo)->ph_id + 1);
	(*philo)->ph->is_dead = 1;
}
