/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args_errors.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfilipe- <hfilipe-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:26:55 by hfilipe-          #+#    #+#             */
/*   Updated: 2025/03/24 12:00:14 by hfilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	check_args2(t_ph *ph, int i)
{
	if (i)
	{
		if (ph->nr_meals < 0)
		{
			put_str_fd(ERROR_MEALS, 2);
			return (1);
		}
	}
	return (0);
}

int	check_args(t_ph *ph, int i)
{
	if (ph->nbr_ph <= 0)
	{
		put_str_fd(ERROR_NBR_PH, 2);
		return (1);
	}
	if (ph->tm_to_d < 0)
	{
		put_str_fd(ERROR_TM_TO_D, 2);
		return (1);
	}
	if (ph->tm_to_s < 0)
	{
		put_str_fd(ERROR_TM_TO_S, 2);
		return (1);
	}
	if (ph->tm_to_e < 0)
	{
		put_str_fd(ERROR_TM_TO_E, 2);
		return (1);
	}
	return (check_args2(ph, i));
}

int	atol_error(void)
{
	put_str_fd("Numeric argument required\n", 2);
	return (-1);
}
