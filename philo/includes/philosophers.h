/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfilipe- <hfilipe-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 09:43:54 by hfilipe-          #+#    #+#             */
/*   Updated: 2025/03/22 14:25:07 by hfilipe-         ###   ########.fr       */
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

typedef struct s_philo	t_p;

typedef struct s_mutex
{
	pthread_mutex_t	mutex;
	int				is_locked;
}	t_mutex;

typedef struct s_philophers
{
	long			nbr_ph;
	long			tm_to_d;
	long			tm_to_s;
	long			tm_to_e;
	long			tm_to_tk;
	long			nr_meals;
	long			st_time;
	long			elapsed_time;
	int				is_dead;
	int				ready;
	int				odd_ate;
	size_t			trh_nbr;
	pthread_t		*threads;
	pthread_t		supervisor;
	t_mutex			*fork;
	t_mutex			wait_to_start;
	t_mutex			ready_m;
	t_mutex			first_meal;
	t_p				*philo;
}	t_ph;

typedef struct s_philo
{
	int				ph_id;
	long			last_meal;
	long			nr_meals;
	t_ph			*ph;
}	t_p;

//										Utilities functions
size_t	str_len(char *str);
void	put_str_fd(char *str, int fd);
long	a_to_l(char *str);
//										Errors Functions
void	atol_error(void);
void	check_args(t_ph *ph, int i);
//										Init functions
void	init_without_times_to_eat(char **av, t_ph *ph);
void	init_with_times_to_eat(char **av, t_ph *ph);
//										Time functions
long	curr_tm(void);
//										Thread functions
void	*actions(void *philosopher);
void	manage_threads(t_ph *ph);
void	phil_eat(t_p **philo, t_mutex **l_fk, t_mutex **r_fk);
void	phil_died(t_p **philo);
void	phil_think(t_p **philo);
void	phil_sleep(t_p **philo);
//										Clean and exit
void	destroy(t_ph *ph);
//										Mutex
void	mutex_init(t_mutex *m);
void	mutex_lock(t_mutex *m);
void	mutex_unlock(t_mutex *m);
int		mutex_locked(t_mutex *m);
void	mutex_destroy(t_mutex *m);
#endif