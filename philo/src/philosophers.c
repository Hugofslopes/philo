/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfilipe- < hfilipe-@student.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:27:12 by hfilipe-          #+#    #+#             */
/*   Updated: 2025/04/29 16:10:30 by hfilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	main(int ac, char**av)
{
	t_meal	ph;

	if (ac == 5)
	{
		if (init(av, &ph, 0))
			return (1);
		manage_threads(&ph);
		destroy(&ph);
	}
	else if (ac == 6)
	{
		if (init(av, &ph, 1))
			return (1);
		manage_threads(&ph);
		destroy(&ph);
	}
	else
	{
		put_str_fd(ERROR_ARG, 2);
		put_str_fd(ERROR_ARG1, 2);
		put_str_fd(ERROR_ARG2, 2);
		put_str_fd(ERROR_ARG3, 2);
	}
}
