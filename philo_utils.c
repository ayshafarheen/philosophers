/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarheen <afarheen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 09:21:03 by afarheen          #+#    #+#             */
/*   Updated: 2023/07/07 16:17:52 by afarheen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
If there is only 1 philosopher, only 1 fork is available so we wait till it
dies and then call the death function.
*/
void	single_philo(t_philo *phs, t_indiv *th)
{
	if (phs->count == 1)
	{
		usleep(phs->die * 1000);
		death(th, phs);
	}
}

/*
Checks the death of a philosopher. If a philosopher is dead we set the
required variable. We check the death by checking if the last eaten time
subtracted from the current time is greater than the time required to die.
in case of death return 1 else 0.
*/
int	death(t_indiv *th, t_philo *phs)
{
	int	flag;

	pthread_mutex_lock(&(phs->dead));
	flag = 0;
	if (phs->isdead == 1)
		flag = 1;
	else if (phs->die <= mil_dif(phs) - th->last_eaten)
	{
		phs->isdead = 1;
		flag = 1;
		pthread_mutex_lock(&(phs->pr));
		printf("\033[0;31m%ld \t %d died\n", mil_dif(phs), th->num + 1);
		pthread_mutex_unlock(&(phs->pr));
	}
	pthread_mutex_unlock(&(phs->dead));
	return (flag);
}

/*
Sleeps for 1 ms and then checks for death
*/
void	my_sleep(t_philo *phs, t_indiv *th2, long int time)
{
	long int	cur;

	cur = mil_dif(phs);
	while (mil_dif(phs) - cur <= time && death(th2, phs) == 0)
		usleep(1000);
}

int	ft_error(void)
{
	write(2, "Error: thread\n", 14);
	return (1);
}

/*
Returns time difference from the start time of the function to the cur time
*/
long int	mil_dif(t_philo *ph)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return (current_time.tv_sec * 1000 + current_time.tv_usec / 1000
		- ph->start_time.tv_sec * 1000 - ph->start_time.tv_usec / 1000);
}
