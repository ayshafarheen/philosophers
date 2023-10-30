/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarheen <afarheen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 08:32:59 by afarheen          #+#    #+#             */
/*   Updated: 2023/07/24 10:39:55 by afarheen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdint.h>
# include <sys/time.h>

typedef struct s_indiv
{
	pthread_t	th;
	int			num;
	int			fork;
	int			sfork;
	void		*main;
	long int	last_eaten;
	int			eat_count;

}t_indiv;

typedef struct s_philo
{
	int				count;
	int				die;
	int				eat;
	int				sleep;
	int				think;
	int				eat_count;
	int				isdead;
	pthread_mutex_t	*mutex;
	pthread_mutex_t	dead;
	pthread_mutex_t	pr;
	t_indiv			*ths;
	struct timeval	start_time;
}t_philo;

void		*ft_calloc(size_t count, size_t size);
void		ft_bzero(void *s, size_t n);
int			ft_str_is_numeric(char *str);
int			ft_atoi(const char *str);
int			verify_and_set(char **nums, t_philo **ph);
void		init_threads(t_philo **phs);
long int	mil_dif(t_philo *ph);
int			ft_error(void);
void		my_sleep(t_philo *phs, t_indiv *th2, long int time);
void		*routine(void *ph);
int			set_forks(t_indiv *th1, t_indiv *th2, t_philo *phs);
int			death(t_indiv *th, t_philo *phs);
void		single_philo(t_philo *phs, t_indiv *th);
int			set_flag(t_indiv *th, t_philo *phs);

#endif
