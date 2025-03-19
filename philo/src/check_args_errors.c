#include "../includes/philosophers.h"

void	check_args2(t_ph *ph, int i)
{
	if (i)
	{
		if (ph->nr_meals < 0)
		{
			put_str_fd(ERROR_MEALS, 2);
			exit (1);
		}
	}
}

void	check_args(t_ph *ph, int i)
{
	if (ph->nbr_ph <= 0)
	{
		put_str_fd(ERROR_NBR_PH, 2);
		exit (1);
	}
	if (ph->tm_to_d < 0)
	{
		put_str_fd(ERROR_TM_TO_D, 2);
		exit (1);
	}
	if (ph->tm_to_s < 0)
	{
		put_str_fd(ERROR_TM_TO_S, 2);
		exit (1);
	}
	if (ph->tm_to_e < 0)
	{
		put_str_fd(ERROR_TM_TO_E, 2);
		exit (1);
	}
	check_args2(ph, i);
}

void	atol_error()
{
    put_str_fd("Numeric argument required\n", 2);
    exit (1);
}