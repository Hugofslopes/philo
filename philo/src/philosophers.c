/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfilipe- <hfilipe-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:27:12 by hfilipe-          #+#    #+#             */
/*   Updated: 2025/03/25 14:30:53 by hfilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	main(int ac, char**av)
{
	t_ph	ph;

	if (ac == 5)
	{
		if (init_without_times_to_eat(av, &ph))
			return (1);
		manage_threads(&ph);
		destroy(&ph);
	}
	else if (ac == 6)
	{
		if (init_with_times_to_eat(av, &ph))
			return (1);
		manage_threads(&ph);
		destroy(&ph);
	}
	else
		put_str_fd(ERROR_ARG, 2);
}
