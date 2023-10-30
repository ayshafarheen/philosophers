/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarheen <afarheen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 07:12:21 by afarheen          #+#    #+#             */
/*   Updated: 2023/07/24 10:05:44 by afarheen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
creates the threads and they start executing by invoking routine(). After
they're created, join() waits for the threads to complete exec.
*/
void	create_and_join(t_philo *phs)
{
	int	flag;
	int	i;

	flag = 0;
	i = 0;
	while (i < phs->count && flag == 0)
	{
		if (pthread_create(&(phs->ths[i].th), NULL,
				&routine, &phs->ths[i]) != 0)
			flag = ft_error();
		i++;
	}
	i = 0;
	while (i < phs->count && flag == 0)
	{
		if (pthread_join(phs->ths[i].th, NULL) != 0)
			flag = ft_error();
		i++;
	}
}

/*
Initializing the required mutexes; overall death, forks, print statements.
Inits the threads as well and sets initial values for the variables.
*/
void	init_threads(t_philo **phs)
{
	int	i;

	i = 0;
	pthread_mutex_init(&(*phs)->dead, NULL);
	pthread_mutex_init(&(*phs)->pr, NULL);
	(*phs)->mutex = malloc((*phs)->count * sizeof(pthread_mutex_t));
	(*phs)->ths = malloc((*phs)->count * sizeof(t_indiv));
	if (!(*phs)->mutex || !(*phs)->ths)
		return ;
	while (i < (*phs)->count)
	{
		pthread_mutex_init(&(*phs)->mutex[i], NULL);
		(*phs)->ths[i].num = i;
		(*phs)->ths[i].sfork = -1;
		(*phs)->ths[i].fork = 1;
		(*phs)->ths[i].main = (*phs);
		(*phs)->ths[i].last_eaten = 0;
		(*phs)->ths[i].eat_count = 0;
		i++;
	}
	create_and_join(*phs);
}

/*
Here the valdity of the arguments is checked, it doesnt accept alphabets,
negative signs or more than 1 positive sign.
*/
int	check_args(char **numbers)
{
	int	i;

	i = 1;
	while (numbers[i])
	{
		if (ft_str_is_numeric(numbers[i]))
			i++;
		else
		{
			write(2, "Error not numeric\n", 18);
			return (0);
		}
	}
	return (1);
}

/*
First checks if the arguments are valid and then converts the arguments to the
necessary values; eat, sleep, die. if there is a certain number of times to eat
to be completed, it stores that as well otherwise -1 is stored. If sleep is not
0, no time to think is given because the greedy philosopher is counted for as
the next philospher would pick uo the fork when this philosopher is sleeping.
*/
int	verify_and_set(char **nums, t_philo **ph)
{
	if (check_args(nums))
	{
		if (ft_atoi(nums[1]) > 200)
			return (0);
		*ph = ft_calloc(1, sizeof(t_philo));
		if (!(*ph))
			return (0);
		gettimeofday(&(*ph)->start_time, NULL);
		(*ph)->count = ft_atoi(nums[1]);
		(*ph)->die = ft_atoi(nums[2]);
		(*ph)->eat = ft_atoi(nums[3]);
		(*ph)->sleep = ft_atoi(nums[4]);
		if ((*ph)->sleep > 0)
			(*ph)->think = 0;
		else
			(*ph)->think = 1;
		if (nums[5])
			(*ph)->eat_count = ft_atoi(nums[5]);
		else
			(*ph)->eat_count = -1;
		return (1);
	}
	return (0);
}
