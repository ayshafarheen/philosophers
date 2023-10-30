/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarheen <afarheen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 09:26:21 by afarheen          #+#    #+#             */
/*   Updated: 2023/07/24 10:48:52 by afarheen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
Set the forks to unavailable, check for death and do the req prints
*/
int	set_forks(t_indiv *th1, t_indiv *th2, t_philo *phs)
{
	th1->fork = 0;
	th2->fork = 0;
	if (death(th2, phs) == 0)
	{
		pthread_mutex_lock(&(phs->pr));
		printf("\033[0;32m%ld\t %d has taken a fork\n",
			mil_dif(phs), th2->num + 1);
		printf("\033[0;32m%ld\t %d has taken a fork\n",
			mil_dif(phs), th2->num + 1);
		pthread_mutex_unlock(&(phs->pr));
	}
	return (1);
}

/*
Call my_sleep for the eating time, once done, set the forks to available
and then update the last eaten time.
*/
void	philo_eat(t_indiv *th1, t_indiv *th2, t_philo *phs)
{
	my_sleep(phs, th2, phs->eat);
	if (th1->num < th2->num)
	{
		pthread_mutex_lock(&(phs->mutex[th1->num]));
		pthread_mutex_lock(&(phs->mutex[th2->num]));
		th1->fork = 1;
		th2->fork = 1;
		th2->sfork = th2->num;
		th1->sfork = th2->num;
		pthread_mutex_unlock(&(phs->mutex[th1->num]));
		pthread_mutex_unlock(&(phs->mutex[th2->num]));
	}
	else
	{
		pthread_mutex_lock(&(phs->mutex[th2->num]));
		pthread_mutex_lock(&(phs->mutex[th1->num]));
		th2->fork = 1;
		th1->fork = 1;
		th2->sfork = th2->num;
		th1->sfork = th2->num;
		pthread_mutex_unlock(&(phs->mutex[th2->num]));
		pthread_mutex_unlock(&(phs->mutex[th1->num]));
	}
	th2->last_eaten = mil_dif(phs);
}

/*
at each step of the way, chekc the death, sleep for the required time, and
print the required action.
*/
void	all_actions(t_indiv *th1, t_indiv *th2, t_philo *phs)
{
	if (death(th2, phs) == 0)
	{
		pthread_mutex_lock(&(phs->pr));
		printf("\033[0;35m%ld\t %d is eating\n", mil_dif(phs), th2->num + 1);
		pthread_mutex_unlock(&(phs->pr));
		philo_eat(th1, th2, phs);
	}
	if (phs->eat_count > -1)
		th2->eat_count++;
	if (death(th2, phs) == 0)
	{
		pthread_mutex_lock(&(phs->pr));
		printf("\033[0;34m%ld\t %d is sleeping\n", mil_dif(phs), th2->num + 1);
		pthread_mutex_unlock(&(phs->pr));
		my_sleep(phs, th2, phs->sleep);
	}
	if (death(th2, phs) == 0)
	{
		pthread_mutex_lock(&(phs->pr));
		printf("\033[0;33m%ld\t %d is thinking\n", mil_dif(phs), th2->num + 1);
		pthread_mutex_unlock(&(phs->pr));
		my_sleep(phs, th2, phs->think);
	}
}

/*
This is the main thread function which is called. It first considers the
case of a single philosopher, then it enters the main while loop which
continually checks if a philosopher is dead or if they're reached the number
of times the philospher needed to eat. Inside the loop, the set_flag() function
checks whether forks are available for a phliospher to eat. If they are
available then the funciton do the required actions are called. Throughout,
the death of the philosopher is checked for.
*/
void	*routine(void *ph)
{
	t_indiv	*th;
	t_philo	*phs;

	th = (t_indiv *) ph;
	phs = (t_philo *) th->main;
	single_philo(phs, th);
	while ((th->eat_count < phs->eat_count || phs->eat_count == -1)
		&& death(th, phs) == 0)
	{
		if (set_flag(th, phs))
		{
			if (th->num == 0)
				all_actions(th + (phs->count - 1), th, phs);
			else
				all_actions(th - 1, th, phs);
		}
		if (death(th, phs))
			break ;
		usleep(1000);
	}
	return (0);
}
