/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfilipe- <hfilipe-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:27:09 by hfilipe-          #+#    #+#             */
/*   Updated: 2025/03/21 18:16:43 by hfilipe-         ###   ########.fr       */
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
			atol_error();
	if (*str == '-' || *str == '+')
		if (*str++ == '-')
			sign *= -1;
	while (*str && *str >= '0' && *str <= '9')
		result = (result * 10) + (*str++ - '0');
	if (*str && (*str < '0' || *str > '9'))
		atol_error();
	return (result * sign);
}
