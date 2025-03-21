/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfilipe- <hfilipe-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:26:37 by hfilipe-          #+#    #+#             */
/*   Updated: 2025/03/21 20:28:23 by hfilipe-         ###   ########.fr       */
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

int	all_ready(t_ph **ph)
{
	if ((*ph)->ready == (*ph)->nbr_ph)
		return (1);
	return (0);
}

void	*monitoring(void *ph)
{
	t_ph	*philos;
	long	i;
	t_p		**phi;

	philos = (t_ph *)ph;

	while(!all_ready(&philos))
		;
	phi = &philos->philo;
	while (!philos->is_dead)
	{
		i = 0;
		phi = phi + i ;
		while (i <  philos->nbr_ph - 1)
		if (curr_tm() - (*phi)->last_meal > philos->tm_to_d)
		{
			printf("%ld %d died\n", (curr_tm() - (*phi)->ph->st_time) \
	/ 999, (*phi)->ph_id);
		(*phi)->ph->is_dead = 1;
		}
	}
	return (NULL);
}

void	init_threads(t_ph *ph)
{
	ph->trh_nbr = 0;
	mutex_init(&ph->wait_to_start);
	mutex_lock(&ph->wait_to_start);
	while (ph->trh_nbr < (size_t)ph->nbr_ph)
	{
		if (pthread_create(&ph->threads[ph->trh_nbr], NULL, actions, \
		&ph->philo[ph->trh_nbr]) != 0)
		{
			put_str_fd("Failed to creat thread", 2);
			exit (1);
		}
		(ph->trh_nbr)++;
	}
	pthread_create(&ph->supervisor, NULL, monitoring, &ph);
	ph->st_time = curr_tm();
	mutex_unlock(&ph->wait_to_start);
}

long	curr_tm(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	init_without_times_to_eat(char **av, t_ph *ph)
{
	ph->nbr_ph = a_to_l(av[1]);
	ph->tm_to_d = a_to_l(av[2]);
	ph->tm_to_s = a_to_l(av[3]);
	ph->tm_to_e = a_to_l(av[4]);
	ph->nr_meals = -1;
	ph->is_dead = 0;
	ph->ready = 1;
	ph->tm_to_tk = ph->tm_to_d - ph->tm_to_s;
	check_args(ph, 0);
	init_philo(ph);
	init_threads(ph);
}

void	init_with_times_to_eat(char **av, t_ph *ph)
{
	ph->nbr_ph = a_to_l(av[1]);
	ph->tm_to_d = a_to_l(av[2]);
	ph->tm_to_s = a_to_l(av[3]);
	ph->tm_to_e = a_to_l(av[4]);
	ph->nr_meals = a_to_l(av[5]);
	ph->is_dead = 0;
	ph->ready = 1;
	ph->tm_to_tk = ph->tm_to_d - ph->tm_to_s;
	check_args(ph, 0);
	init_philo(ph);
	init_threads(ph);
}
