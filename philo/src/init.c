/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfilipe- <hfilipe-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:26:37 by hfilipe-          #+#    #+#             */
/*   Updated: 2025/03/25 14:30:49 by hfilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	init_philo(t_ph *ph)
{
	ph->trh_nbr = 0;
	ph->fork = malloc(sizeof(t_mutex) * ph->nbr_ph);
	ph->threads = malloc(sizeof(pthread_t) * ph->nbr_ph);
	ph->philo = malloc(sizeof(t_p) * ph->nbr_ph);
	while (ph->trh_nbr < (size_t)ph->nbr_ph)
	{
		ph->philo[ph->trh_nbr].ph_id = ph->trh_nbr;
		ph->philo[ph->trh_nbr].ph = ph;
		ph->philo[ph->trh_nbr].nr_meals = 0;
		mutex_init(&ph->fork[ph->trh_nbr]);
		ph->trh_nbr++;
	}
}

void	init_eat_time(t_ph *ph)
{
	long	i;
	t_p		*philo;

	i = 0;
	while (i < ph->nbr_ph)
	{
		philo = ph->philo + i;
		philo->last_meal = curr_tm();
		i++;
	}
	ph->st_time = curr_tm();
}

int	init_threads(t_ph *ph)
{
	ph->trh_nbr = 0;
	mutex_init(&ph->wait_to_start);
	mutex_init(&ph->ready_m);
	mutex_init(&ph->first_meal);
	mutex_lock(&ph->wait_to_start);
	while (ph->trh_nbr < (size_t)ph->nbr_ph)
	{
		if (pthread_create(&ph->threads[ph->trh_nbr], NULL, actions, \
		&ph->philo[ph->trh_nbr]) != 0)
		{
			put_str_fd("Failed to creat thread", 2);
			return (1);
		}
		(ph->trh_nbr)++;
	}
	init_eat_time(ph);
	pthread_create(&ph->supervisor, NULL, monitoring, ph);
	mutex_unlock(&ph->wait_to_start);
	return (0);
}

int	init_without_times_to_eat(char **av, t_ph *ph)
{
	if (a_tols(ph, av))
		return (1);
	ph->nr_meals = -1;
	ph->is_dead = 0;
	ph->ready = 0;
	ph->odd_ate = 0;
	ph->tm_to_tk = (ph->tm_to_d - ph->tm_to_s - ph->tm_to_e) / 2;
	if (ph->nbr_ph == 1)
		return (one_philo(&ph), 1);
	if (check_args(ph, 0))
		return (1);
	init_philo(ph);
	if (init_threads(ph))
		return (1);
	return (0);
}

int	init_with_times_to_eat(char **av, t_ph *ph)
{
	if (a_tols2(ph, av))
		return (1);
	ph->is_dead = 0;
	ph->ready = 0;
	ph->odd_ate = 0;
	ph->tm_to_tk = (ph->tm_to_d - ph->tm_to_s - ph->tm_to_e) / 2;
	if (ph->nbr_ph == 1)
		return (one_philo(&ph), 1);
	if (check_args(ph, 1))
		return (1);
	init_philo(ph);
	if (init_threads(ph))
		return (1);
	return (0);
}
