/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfilipe- <hfilipe-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:27:03 by hfilipe-          #+#    #+#             */
/*   Updated: 2025/03/21 17:30:13 by hfilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	destroy(t_ph *ph)
{
	long	i;

	free(ph->fork);
	free(ph->threads);
	i = 0;
	while (i < ph->nbr_ph)
		mutex_destroy(&ph->fork[i++]);
}
