/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfilipe- <hfilipe-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:27:03 by hfilipe-          #+#    #+#             */
/*   Updated: 2025/03/25 21:57:29 by hfilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	destroy(t_ph **ph)
{
	long	i;

	free((*ph)->fork);
	free((*ph)->threads);
	free((*ph)->philo);
	i = 0;
	while (i < (*ph)->nbr_ph)
		mutex_destroy(&(*ph)->fork[i++]);
	mutex_destroy(&(*ph)->wait_to_start);
	mutex_destroy(&(*ph)->ready_m);
	mutex_destroy(&(*ph)->first_meal);
}
