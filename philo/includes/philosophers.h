/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfilipe- <hfilipe-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 09:43:54 by hfilipe-          #+#    #+#             */
/*   Updated: 2025/03/17 15:24:40 by hfilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

# define ERROR_ARG "Invalid number of arguments\n Please insert: \
<number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> \
optional: <number_of_times_each_philosopher_must_eat>\n"
# define ERROR_NBR_PH "The program needs at least 1 philosopher to execute\n" 
# define ERROR_MEALS "The number of meals must be equal or great then 0\n" 
# define ERROR_TM_TO_D "The time to die must be equal or great then 0\n" 
# define ERROR_TM_TO_S "The time to sleep must be equal or great then 0\n"
# define ERROR_TM_TO_E "The time to eat must be equal or great then 0\n"

typedef struct	s_philophers
{
	long			nbr_ph;
	long			tm_to_d;
	long			tm_to_s;
	long			tm_to_e;
	long			nr_meals;
	long			tm_of_day;
	size_t			trh_nbr;
	pthread_t		*threads;
	pthread_mutex_t	*fork;
}	t_ph;

//Utilities functions
size_t  str_len(char *str);
void	put_str_fd(char *str, int fd);
long	a_to_l(char *str);

//Errors Functions
void	atol_error();
void	check_args(t_ph **ph, int i);

//Init functions
void	init_without_times_to_eat(char **av, t_ph **ph);
void	init_with_times_to_eat(char **av,t_ph **ph);

//Thread functions
void	*thread_function(void *ph);
#endif