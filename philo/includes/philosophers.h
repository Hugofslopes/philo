/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfilipe- <hfilipe-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 09:43:54 by hfilipe-          #+#    #+#             */
/*   Updated: 2025/04/21 13:41:45 by hfilipe-         ###   ########.fr       */
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
# define ERROR_ZERO_M "All philosophers ate the required number of \
meals.\n"

typedef struct s_philo	t_p;

typedef enum
{
    READY_M,
    MEALS_ATE,
    FRST_M,
    FINISHED,
    CRR_TM,
    READY_TO_GOM,
    NUM_MUTEXES
} MutexEnum;

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
	int				m_finished;
	int				ready;
	int				fm_ate;
	int				ready_to_go;
	int				all_ate;
	size_t			trh_nbr;
	pthread_t		*threads;
	pthread_t		supervisor;
	pthread_mutex_t	*fork;
	pthread_mutex_t	mutex[NUM_MUTEXES];
	t_p				*philo;
}	t_meal;

typedef struct s_philo
{
	int				ph_id;
	long			tm_to_d;
	long			tm_to_s;
	long			tm_to_e;
	long			tm_to_tk;
	long			nbr_philo;
	long			st_time;
	long			last_meal;
	long			nr_meals;
	long			meals_ate	;
	t_meal			*ph;
	pthread_mutex_t	*l_fk;
	pthread_mutex_t	*r_fk;
}	t_p;

//										Utilities functions
size_t	str_len(char *str);
void	put_str_fd(char *str, int fd);
long	a_to_l(char *str);
int		a_tols(t_meal *ph, char **av, int i);
void	one_philo(t_meal **ph);
int		count_odd_phil(int x);
//										Errors Functions
int		atol_error(void);
int		check_args(t_meal *ph);
//										Init functions
int		init(char **av, t_meal *ph, int i);
//										Time functions
long	curr_tm(void);
//										Thread functions
void	*actions(void *philosopher);
void	manage_threads(t_meal *ph);
void	phil_eat(t_p **philo);
void	phil_died(t_p *philo);
void	phil_think(t_p **philo);
void	phil_sleep(t_p **philo);
void	execute_odds(t_p **philo);
void	execute_even(t_p **philo);
//										Clean and exit
void	destroy(t_meal *ph);
//										Monitoring
void	*monitoring(void *ph);
//										Mutex
int		mutex_locked(pthread_mutex_t *m);
//										Loops
int		meals_loop(t_p **philo);
#endif