/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfilipe- <hfilipe-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:27:12 by hfilipe-          #+#    #+#             */
/*   Updated: 2025/03/25 22:16:09 by hfilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	main(int ac, char**av)
{
	t_ph	*meal;

	meal = malloc(sizeof(t_ph));
	if (ac == 5)
	{
		if (init_without_times_to_eat(av, &meal))
			return (1);
		manage_threads(&meal);
		destroy(&meal);
	}
	else if (ac == 6)
	{
		if (init_with_times_to_eat(av, &meal))
			return (1);
		manage_threads(&meal);
		destroy(&meal);
	}
	else
	{
		free(meal);
		put_str_fd(ERROR_ARG, 2);
		return (1);
	}
	return (0);
}
