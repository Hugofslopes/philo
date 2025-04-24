/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfilipe- <hfilipe-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:26:50 by hfilipe-          #+#    #+#             */
/*   Updated: 2025/04/24 13:44:17 by hfilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	phil_eat_f(t_p **philo)
{
	if ((*philo)->ph_id == (*philo)->nbr_philo - 1)
	{
		pthread_mutex_lock((*philo)->l_fk);
		pthread_mutex_lock((*philo)->r_fk);
	}
	else
	{
		pthread_mutex_lock((*philo)->r_fk);
		pthread_mutex_lock((*philo)->l_fk);
	}
}

void	phil_eat(t_p **philo)
{
	phil_eat_f(philo);
	pthread_mutex_lock(&(*philo)->ph->mutex[CRR_TM]);
	printf("%ld %d has taken a fork\n", (curr_tm() - (*philo)->st_time) \
	, (*philo)->ph_id + 1);
	printf("%ld %d has taken a fork\n", (curr_tm() - (*philo)->st_time) \
	, (*philo)->ph_id + 1);
	(*philo)->last_meal = curr_tm();
	printf("%ld %d is eating\n", (curr_tm() - (*philo)->st_time), \
	(*philo)->ph_id + 1);
	pthread_mutex_unlock(&(*philo)->ph->mutex[CRR_TM]);
	pthread_mutex_lock(&(*philo)->ph->mutex[FRST_M]);
	(*philo)->ph->fm_ate++;
	pthread_mutex_unlock(&(*philo)->ph->mutex[FRST_M]);
	usleep((*philo)->tm_to_e * 1000);
	pthread_mutex_unlock((*philo)->l_fk);
	pthread_mutex_unlock((*philo)->r_fk);
	pthread_mutex_lock(&(*philo)->ph->mutex[MEALS_ATE]);
	(*philo)->meals_ate++;
	pthread_mutex_unlock(&(*philo)->ph->mutex[MEALS_ATE]);
}

void	phil_sleep(t_p **philo)
{
	pthread_mutex_lock(&(*philo)->ph->mutex[CRR_TM]);
	printf("%ld %d is sleeping\n", (curr_tm() - (*philo)->st_time) \
, (*philo)->ph_id + 1);
	pthread_mutex_unlock(&(*philo)->ph->mutex[CRR_TM]);
	usleep((*philo)->tm_to_s * 1000);
}

void	phil_think(t_p **philo)
{
	pthread_mutex_lock(&(*philo)->ph->mutex[CRR_TM]);
	printf("%ld %d is thinking\n", (curr_tm() - (*philo)->st_time) \
, (*philo)->ph_id + 1);
	pthread_mutex_unlock(&(*philo)->ph->mutex[CRR_TM]);
	usleep((*philo)->tm_to_tk * 1000);
}

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
