#include "../includes/philosophers.h"

void	init_philo(t_ph **ph)
{
	(*ph)->trh_nbr = 0;
	(*ph)->fork = malloc(sizeof(pthread_mutex_t) * (*ph)->nbr_ph);
	(*ph)->threads = malloc(sizeof(pthread_t) * (*ph)->nbr_ph);
	(*ph)->philo = malloc(sizeof(t_p) * (*ph)->nbr_ph);
	while ((*ph)->trh_nbr < (size_t)(*ph)->nbr_ph)
	{
		(*ph)->philo[(*ph)->trh_nbr].ph_id = (*ph)->trh_nbr;
		(*ph)->philo[(*ph)->trh_nbr].ph = *ph;
		(*ph)->philo[(*ph)->trh_nbr].last_meal = (*ph)->st_time;
		(*ph)->philo[(*ph)->trh_nbr].nr_meals = 0;
		pthread_mutex_init(&(*ph)->fork[(*ph)->trh_nbr], NULL);
		(*ph)->trh_nbr++;
	}
}

void	init_threads(t_ph **ph)
{
	(*ph)->trh_nbr = 0;
	while ((*ph)->trh_nbr < (size_t)(*ph)->nbr_ph)
	{
		(*ph)->threads[(*ph)->trh_nbr] = (*ph)->trh_nbr;
		if (pthread_create(&(*ph)->threads[(*ph)->trh_nbr], NULL, actions, \
		&(*ph)->philo[(*ph)->trh_nbr]) != 0)
		{
            put_str_fd("Failed to creat thread", 2);
            exit (1);
		}
		((*ph)->trh_nbr)++;
	}
}

long long curr_tm()
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 999) + (tv.tv_usec / 999);
}

void	init_without_times_to_eat(char **av, t_ph **ph)
{
	(*ph)->nbr_ph = a_to_l(av[1]);
	(*ph)->tm_to_d = a_to_l(av[2]);
	(*ph)->tm_to_s = a_to_l(av[3]);
	(*ph)->tm_to_e = a_to_l(av[4]);
	(*ph)->nr_meals = -1;
	(*ph)->is_dead = 0;
	(*ph)->st_time = curr_tm();
	(*ph)->tm_to_tk = (*ph)->tm_to_d - (*ph)->tm_to_s;
	check_args(ph, 0);
	init_philo(ph);
	init_threads(ph);
}

void	init_with_times_to_eat(char **av,t_ph **ph)
{
	(*ph)->nbr_ph = a_to_l(av[1]);
	(*ph)->tm_to_d = a_to_l(av[2]);
	(*ph)->tm_to_s = a_to_l(av[3]);
	(*ph)->tm_to_e = a_to_l(av[4]);
	(*ph)->nr_meals = a_to_l(av[5]);
	(*ph)->is_dead = 0;
	(*ph)->st_time = curr_tm();
	(*ph)->tm_to_tk = (*ph)->tm_to_d - (*ph)->tm_to_s;
	check_args(ph, 0);
	init_philo(ph);
	init_threads(ph);
}
