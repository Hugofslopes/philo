#include "../includes/philosophers.h"

int	main(int ac, char**av)
{
	t_ph ph;

	if (ac == 5)
	{
		init_without_times_to_eat(av, &ph);
		manage_threads(&ph);
		destroy(&ph);
	}
	else if (ac == 6)
	{
		init_with_times_to_eat(av, &ph);
		manage_threads(&ph);
		destroy(&ph);
	}
	else
		put_str_fd(ERROR_ARG, 2);
}
