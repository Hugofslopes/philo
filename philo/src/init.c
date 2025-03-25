/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfilipe- <hfilipe-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:26:37 by hfilipe-          #+#    #+#             */
/*   Updated: 2025/03/25 22:18:56 by hfilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	init_philo(t_ph **meal)
{
	(*meal)->trh_nbr = 0;
	(*meal)->fork = malloc(sizeof(t_mutex) * (*meal)->nbr_ph);
	(*meal)->threads = malloc(sizeof(pthread_t) * (*meal)->nbr_ph);
	(*meal)->philo = malloc(sizeof(t_p) * (*meal)->nbr_ph);
	while ((*meal)->trh_nbr < (size_t)(*meal)->nbr_ph)
	{
		(*meal)->philo[(*meal)->trh_nbr].ph_id = (*meal)->trh_nbr;
		(*meal)->philo[(*meal)->trh_nbr].meal = (*meal);
		(*meal)->philo[(*meal)->trh_nbr].nr_meals = 0;
		(*meal)->philo[(*meal)->trh_nbr].t_to_d = (*meal)->tm_to_d;
		(*meal)->philo[(*meal)->trh_nbr].t_to_e = (*meal)->tm_to_e;
		(*meal)->philo[(*meal)->trh_nbr].t_to_s = (*meal)->tm_to_s;
		(*meal)->philo[(*meal)->trh_nbr].t_to_t = (*meal)->tm_to_tk;
		mutex_init(&(*meal)->fork[(*meal)->trh_nbr]);
		(*meal)->trh_nbr++;
	}
}

void	init_eat_time(t_ph **meal)
{
	long	i;
	t_p		*philo;

	i = 0;
	while (i < (*meal)->nbr_ph)
	{
		philo = (*meal)->philo + i;
		philo->last_meal = curr_tm();
		philo->st_time = philo->last_meal;
		i++;
	}
	(*meal)->st_time = curr_tm();
}

int	init_threads(t_ph **meal)
{
	(*meal)->trh_nbr = 0;
	mutex_init(&(*meal)->wait_to_start);
	mutex_init(&(*meal)->ready_m);
	mutex_init(&(*meal)->first_meal);
	mutex_lock(&(*meal)->wait_to_start);
	while ((*meal)->trh_nbr < (size_t)(*meal)->nbr_ph)
	{
		if (pthread_create(&(*meal)->threads[(*meal)->trh_nbr], NULL, actions, \
		&(*meal)->philo[(*meal)->trh_nbr]) != 0)
		{
			put_str_fd("Failed to creat thread", 2);
			return (1);
		}
		(*meal)->trh_nbr++;
	}
	init_eat_time(meal);
	pthread_create(&(*meal)->supervisor, NULL, monitoring, (*meal));
	mutex_unlock(&(*meal)->wait_to_start);
	return (0);
}

int	init_without_times_to_eat(char **av, t_ph **meal)
{
	if (a_tols(meal, av))
		return (1);
	(*meal)->nr_meals = -1;
	(*meal)->is_dead = 0;
	(*meal)->ready = 0;
	(*meal)->odd_ate = 0;
	(*meal)->tm_to_tk = ((*meal)->tm_to_d - (*meal)->tm_to_s - (*meal)->tm_to_e) / 2;
	if ((*meal)->nbr_ph == 1)
		return (one_philo(meal), 1);
	if (check_args(meal, 0))
		return (1);
	init_philo(meal);
	if (init_threads(meal))
		return (1);
	return (0);
}

int	init_with_times_to_eat(char **av, t_ph **meal)
{
	if (a_tols2(meal, av))
		return (1);
	(*meal)->is_dead = 0;
	(*meal)->ready = 0;
	(*meal)->odd_ate = 0;
	(*meal)->tm_to_tk = ((*meal)->tm_to_d - (*meal)->tm_to_s - (*meal)->tm_to_e) / 2;
	if ((*meal)->nbr_ph == 1)
		return (one_philo(meal), 1);
	if (check_args(meal, 1))
		return (1);
	init_philo(meal);
	if (init_threads(meal))
		return (1);
	return (0);
}
