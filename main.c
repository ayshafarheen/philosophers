/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarheen <afarheen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 09:18:04 by afarheen          #+#    #+#             */
/*   Updated: 2023/07/07 16:30:08 by afarheen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_philo			*ph;
	int				i;

	if (argc >= 5 && argc < 7)
	{
		if (verify_and_set(argv, &ph) && ph)
		{
			init_threads(&ph);
			i = 0;
			if (ph->ths)
				free(ph->ths);
			while (i < ph->count)
				pthread_mutex_destroy(&(ph)->mutex[i++]);
			pthread_mutex_destroy(&(ph)->pr);
			pthread_mutex_destroy(&(ph)->dead);
			if (ph->mutex)
				free(ph->mutex);
			free(ph);
		}
	}
	else
		write(2, "Error wrong num of args\n", 24);
}
