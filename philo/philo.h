/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchaguer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 18:51:44 by hchaguer          #+#    #+#             */
/*   Updated: 2023/06/07 07:08:06 by hchaguer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <ctype.h>
# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_data
{
	pthread_mutex_t	print;
	int				number_of_philos;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_think;
	int				time_to_die;
	int				nb_of_times_each_philo_must_eat;
	int				ate_max;
	int				last;
	int				x;
	int				n_eat;
	int				etat;
}					t_data;

typedef struct s_philo
{
	int				id;
	int				cur_time;
	int				etat;
	int				last_meal;
	pthread_mutex_t	fork;
	t_data			*data;
	pthread_t		thread;
	struct s_philo	*next;
}					t_philo;

int					ft_atoi(char *str);
void				ft_lstadd_back(t_philo **head, t_philo *node1);
t_philo				*create_node(int id, t_data *data);
int					cur_time(void);
int					is_integer(const char *str);
int					ft_isdigit(int c);
void				join_thread(t_philo *philo, t_data data, int i);
int					create_philo(t_philo *philo, t_data data, int i);
int					check_death(int ac, t_data *data, t_philo *philo);
void				innit_args(t_data *data, int ac, char **av);
void				init_philo(t_philo **philo, t_data *data);
int					check_args(int ac, char **av);
void				ft_wait(int time);
void				*test(void *t1);
void				eatt(t_philo *t, t_data *data);

#endif
