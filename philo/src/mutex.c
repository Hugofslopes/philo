/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfilipe- <hfilipe-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 14:52:35 by hfilipe-          #+#    #+#             */
/*   Updated: 2025/04/14 16:00:49 by hfilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	mutex_locked(pthread_mutex_t *m)
{
	if (!pthread_mutex_lock(m))
	{
		pthread_mutex_unlock(m);
		return (0);
	}
	return (1);
}
