/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfilipe- <hfilipe-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:26:26 by hfilipe-          #+#    #+#             */
/*   Updated: 2025/03/21 17:29:12 by hfilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	mutex_init(t_mutex *m)
{
	pthread_mutex_init(&m->mutex, NULL);
	m->is_locked = 0;
}

void	mutex_lock(t_mutex *m)
{
	pthread_mutex_lock(&m->mutex);
	m->is_locked = 1;
}

void	mutex_unlock(t_mutex *m)
{
	m->is_locked = 0;
	pthread_mutex_unlock(&m->mutex);
}

int	mutex_locked(t_mutex *m)
{
	return (m->is_locked);
}

void	mutex_destroy(t_mutex *m)
{
	pthread_mutex_destroy(&m->mutex);
}
