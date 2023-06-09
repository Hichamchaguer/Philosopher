/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchaguer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 20:21:49 by hchaguer          #+#    #+#             */
/*   Updated: 2023/06/07 04:57:13 by hchaguer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <limits.h>
# include <sys/time.h>
# include <semaphore.h>
# include <signal.h>

typedef struct s_philo
{
	int				x;
	struct timeval	last_meal;
	int				nb_forks;
	int				ate_max;
	int				id;
	int				cur_time;
	int				etat;
	int				number_of_philos;
	int				y;
	int				n_time;
	int				ac;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_think;
	int				last_time;
	int				nb_of_times_each_philo_must_eat;
	int				number_forks;
	int				*pid;
	unsigned int	time_to_die;
	pthread_t		thread;
	sem_t			*fork;
	sem_t			*print;
	sem_t			*lst;
}	t_philo;

unsigned int	cur_time(void);
int				check_args(int ac, char **av);
int				ft_atoi(const char *str);
void			*check_death(void *t1);
void			create_philo(t_philo *philo);
void			innit_args(t_philo *philo, int ac, char **av);
void			init_philo(t_philo *philo);
void			ft_wait(unsigned int time);
void			test(t_philo philo);
void			eatt(t_philo *philo);
void			ft_kill(t_philo philo);
int				get_time(struct timeval last);
int				is_integer(const char *str);
#endif
