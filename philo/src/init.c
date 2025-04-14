/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfilipe- <hfilipe-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:26:37 by hfilipe-          #+#    #+#             */
/*   Updated: 2025/04/14 16:03:19 by hfilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	init_philo(t_meal *meal, long i)
{
	meal->fork = malloc(sizeof(pthread_mutex_t) * meal->nbr_ph);
	meal->threads = malloc(sizeof(pthread_t) * meal->nbr_ph);
	meal->philo = malloc(sizeof(t_p) * meal->nbr_ph);
	while (i < meal->nbr_ph)
	{
		meal->philo[i].ph_id = i;
		meal->philo[i].ph = meal;
		meal->philo[i].nr_meals = meal->nr_meals;
		meal->philo[i].meals_ate = 0;
		meal->philo[i].tm_to_d = meal->tm_to_d;
		meal->philo[i].tm_to_e = meal->tm_to_e;
		meal->philo[i].tm_to_s = meal->tm_to_s;
		meal->philo[i].tm_to_tk = meal->tm_to_tk;
		meal->philo[i].nbr_philo = meal->nbr_ph;
		meal->philo[i].r_fk = &meal->fork[i];
		if (i == meal->nbr_ph - 1)
			meal->philo[i].l_fk = &meal->fork[0];
		else
			meal->philo[i].l_fk = &meal->fork[i + 1];
		pthread_mutex_init(&meal->fork[i], NULL);
		i++;
	}
}

void	init_eat_time(t_meal *meal)
{
	long	i;
	t_p		*philo;

	i = 0;
	while (i < meal->nbr_ph)
	{
		philo = meal->philo + i;
		pthread_mutex_lock(&meal->crr_tm);
		philo->last_meal = curr_tm();
		pthread_mutex_unlock(&meal->crr_tm);
		philo->st_time = philo->last_meal;
		i++;
	}
	meal->st_time = curr_tm();
}

int	init_threads(t_meal *meal)
{
	meal->trh_nbr = 0;
	pthread_mutex_init(&meal->ready_m, NULL);
	pthread_mutex_init(&meal->first_meal, NULL);
	pthread_mutex_init(&meal->finished, NULL);
	pthread_mutex_init(&meal->crr_tm, NULL);
	pthread_mutex_init(&meal->ready_to_gom, NULL);
	pthread_mutex_init(&meal->meals_ate, NULL);
	while (meal->trh_nbr < (size_t)meal->nbr_ph)
	{
		if (pthread_create(&(meal)->threads[meal->trh_nbr], NULL, actions, \
		&meal->philo[meal->trh_nbr]) != 0)
		{
			put_str_fd("Failed to creat thread", 2);
			return (1);
		}
		(meal->trh_nbr)++;
	}
	init_eat_time(meal);
	pthread_create(&meal->supervisor, NULL, monitoring, meal);
	pthread_mutex_lock(&meal->ready_to_gom);
	meal->ready_to_go++;
	pthread_mutex_unlock(&meal->ready_to_gom);
	return (0);
}

int	init(char **av, t_meal *meal, int i)
{
	if (a_tols(meal, av, i))
		return (1);
	if (!i)
		meal->nr_meals = -1;
	meal->m_finished = 0;
	meal->ready = 0;
	meal->odd_ate = 0;
	meal->all_ate = 0;
	meal->ready_to_go = 0;
	meal->odd_ph = count_odd_phil(meal->nbr_ph);
	meal->tm_to_tk = (meal->tm_to_d - meal->tm_to_s - meal->tm_to_e) / 2;
	if (meal->tm_to_tk < 0)
		meal->tm_to_tk = 5;
	if (meal->nbr_ph == 1)
		return (one_philo(&meal), 1);
	if (check_args(meal, 0))
		return (1);
	init_philo(meal, 0);
	if (init_threads(meal))
		return (1);
	return (0);
}
