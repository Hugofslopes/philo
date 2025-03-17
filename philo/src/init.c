#include "../includes/philosophers.h"

void init_threads(t_ph **ph)
{
	(*ph)->trh_nbr = 1;
	(*ph)->threads = malloc(sizeof(pthread_t) * (*ph)->nbr_ph);
	while ((*ph)->trh_nbr <= (size_t)(*ph)->nbr_ph)
	{
		(*ph)->threads[(*ph)->trh_nbr] = (*ph)->trh_nbr;
		pthread_mutex_init(&(*ph)->fork[(*ph)->trh_nbr], NULL);
		if (pthread_create(&(*ph)->threads[(*ph)->trh_nbr], NULL, thread_function, (void *) ph) != 0)
		{
            put_str_fd("Failed to creat thread", 2);
            exit (1);
		}
		((*ph)->trh_nbr)++;
	}
	while ((*ph)->trh_nbr)
		pthread_mutex_destroy(&(*ph)->fork[(*ph)->trh_nbr--]);
}

void	init_without_times_to_eat(char **av, t_ph **ph)
{
	struct timeval tv;

	(*ph)->nbr_ph = a_to_l(av[1]);
	(*ph)->tm_to_d = a_to_l(av[2]);
	(*ph)->tm_to_s = a_to_l(av[3]);
	(*ph)->tm_to_e = a_to_l(av[4]);
	(*ph)->nr_meals = -1;
	check_args(ph, 0);
	init_threads(ph);
		(*ph)->tm_of_day = gettimeofday(&tv, NULL);
    printf("Seconds: %ld\n", tv.tv_sec);
    printf("Microseconds: %ld\n", tv.tv_usec);
}

void	init_with_times_to_eat(char **av,t_ph **ph)
{
	(*ph)->nbr_ph = a_to_l(av[1]);
	(*ph)->tm_to_d = a_to_l(av[2]);
	(*ph)->tm_to_s = a_to_l(av[3]);
	(*ph)->tm_to_e = a_to_l(av[4]);
	(*ph)->nr_meals = a_to_l(av[5]);
	check_args(ph, 1);
}
