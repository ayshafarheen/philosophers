/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarheen <afarheen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 09:48:38 by afarheen          #+#    #+#             */
/*   Updated: 2023/07/24 10:48:02 by afarheen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	fork_util1(t_indiv *th1, t_indiv *th2, t_philo *phs)
{
	int	flag;

	flag = 0;
	pthread_mutex_lock(&(phs->mutex[th1->num]));
	pthread_mutex_lock(&(phs->mutex[th2->num]));
	if (th1->fork == 1 && th2->fork == 1
		&& th1->sfork != th1->num && th2->sfork != th1->num)
		flag = set_forks(th2, th1, phs);
	pthread_mutex_unlock(&(phs->mutex[th1->num]));
	pthread_mutex_unlock(&(phs->mutex[th2->num]));
	return (flag);
}

int	fork_util2(t_indiv *th1, t_indiv *th2, t_philo *phs)
{
	int	flag;

	flag = 0;
	pthread_mutex_lock(&(phs->mutex[th1->num]));
	pthread_mutex_lock(&(phs->mutex[th2->num]));
	if (th1->fork == 1 && th2->fork == 1
		&& th1->sfork != th2->num && th2->sfork != th2->num)
		flag = set_forks(th1, th2, phs);
	pthread_mutex_unlock(&(phs->mutex[th1->num]));
	pthread_mutex_unlock(&(phs->mutex[th2->num]));
	return (flag);
}

/*
according to the position of the philosopher, check for availability of forks
and if they're avialable, set the forks to unavailable.
*/
int	set_flag(t_indiv *th, t_philo *phs)
{
	int	flag;

	flag = 0;
	if (th->num == 0)
		flag = fork_util1(th, th + (phs->count - 1), phs);
	else if (th->num != 0)
		flag = fork_util2(th - 1, th, phs);
	return (flag);
}
