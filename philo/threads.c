/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchaguer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 22:23:21 by hchaguer          #+#    #+#             */
/*   Updated: 2023/06/07 22:33:16 by hchaguer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_philo(t_philo *philo, t_data data, int i)
{
	while (i < data.number_of_philos)
	{
		if (pthread_create(&philo->thread, NULL, test, philo) != 0)
			return (1);
		philo = philo->next;
		i++;
	}
	return (0);
}

void	join_thread(t_philo *philo, t_data data, int i)
{
	while (i < data.number_of_philos)
	{
		pthread_join(philo->thread, NULL);
		philo = philo->next;
		i++;
	}
}

void	sleep_think(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(&data->print);
	printf("%d %d is sleeping\n", cur_time() - philo->cur_time, philo->id);
	pthread_mutex_unlock(&data->print);
	ft_wait(data->time_to_sleep);
	pthread_mutex_lock(&data->print);
	printf("%d %d is thinking\n", cur_time() - philo->cur_time, philo->id);
	pthread_mutex_unlock(&data->print);
}

void	*test(void *t1)
{
	t_philo	*t;
	t_data	*data;
	int		n_eat;

	n_eat = 0;
	t = (t_philo *)t1;
	data = t->data;
	if (t->id % 2 == 0)
		usleep(200);
	while (1)
	{
		eatt(t, data);
		if (t->data->nb_of_times_each_philo_must_eat == ++n_eat)
		{
			pthread_mutex_lock(&data->print);
			t->data->ate_max++;
			pthread_mutex_unlock(&data->print);
		}
		sleep_think(t, data);
	}
}

void	eatt(t_philo *t, t_data *data)
{
	pthread_mutex_lock(&t->fork);
	pthread_mutex_lock(&data->print);
	printf("%d %d has taken a fork\n", cur_time() - t->cur_time, t->id);
	pthread_mutex_unlock(&data->print);
	pthread_mutex_lock(&t->next->fork);
	pthread_mutex_lock(&data->print);
	printf("%d %d has taken a fork\n", cur_time() - t->cur_time, t->id);
	pthread_mutex_unlock(&data->print);
	pthread_mutex_lock(&data->print);
	printf("%d %d is eating\n", cur_time() - t->cur_time, t->id);
	pthread_mutex_unlock(&data->print);
	pthread_mutex_lock(&data->print);
	t->last_meal = cur_time() - t->cur_time;
	pthread_mutex_unlock(&data->print);
	ft_wait(data->time_to_eat);
	pthread_mutex_unlock(&t->next->fork);
	pthread_mutex_unlock(&t->fork);
}
