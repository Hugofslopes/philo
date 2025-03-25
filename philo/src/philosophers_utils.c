/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfilipe- <hfilipe-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:27:09 by hfilipe-          #+#    #+#             */
/*   Updated: 2025/03/25 13:53:45 by hfilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

size_t	str_len(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	put_str_fd(char *str, int fd)
{
	write(fd, str, str_len(str));
}

long	a_to_l(char *str)
{
	int			sign;
	long		result;

	sign = 1;
	result = 0;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str != '-' && *str != '+')
		if (*str && (*str < '0' || *str > '9'))
			return (atol_error());
	if (*str == '-' || *str == '+')
		if (*str++ == '-')
			sign *= -1;
	while (*str && *str >= '0' && *str <= '9')
		result = (result * 10) + (*str++ - '0');
	if (*str && (*str < '0' || *str > '9'))
		return (atol_error());
	return (result * sign);
}

int	a_tols(t_ph *ph, char **av)
{
	ph->nbr_ph = a_to_l(av[1]);
	if (ph->nbr_ph == -1)
		return (put_str_fd("Wrong input on number of philosophers\n", 1), 1);
	ph->tm_to_d = a_to_l(av[2]);
	if (ph->tm_to_d == -1)
		return (put_str_fd("Wrong input on time to die\n", 1), 1);
	ph->tm_to_e = a_to_l(av[3]);
	if (ph->tm_to_e == -1)
		return (put_str_fd("Wrong input on time to sleep\n", 1), 1);
	ph->tm_to_s = a_to_l(av[4]);
	if (ph->tm_to_s == -1)
		return (put_str_fd("Wrong input on time to eat\n", 1), 1);
	return (0);
}

int	a_tols2(t_ph *ph, char **av)
{
	ph->nbr_ph = a_to_l(av[1]);
	if (ph->nbr_ph == -1)
		return (put_str_fd("Wrong input on number of philosophers\n", 1), 1);
	ph->tm_to_d = a_to_l(av[2]);
	if (ph->tm_to_d == -1)
		return (put_str_fd("Wrong input on time tos die\n", 1), 1);
	ph->tm_to_e = a_to_l(av[3]);
	if (ph->tm_to_e == -1)
		return (put_str_fd("Wrong input on time to sleep\n", 1), 1);
	ph->tm_to_s = a_to_l(av[4]);
	if (ph->tm_to_s == -1)
		return (put_str_fd("Wrong input on time to eat\n", 1), 1);
	ph->nr_meals = a_to_l(av[5]);
	if (ph->nr_meals == -1)
		return (put_str_fd("Wrong input on number of meals\n", 1), 1);
	return (0);
}
