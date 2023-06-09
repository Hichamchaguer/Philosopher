/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchaguer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 18:51:32 by hchaguer          #+#    #+#             */
/*   Updated: 2023/06/07 22:38:36 by hchaguer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*test1(void *t1)
{
	t_data	*data;
	t_philo	*t;

	t = (t_philo *)t1;
	data = t->data;
	printf("%d %d has taken a fork\n", cur_time() - t->cur_time, t->id);
	ft_wait(data->time_to_die);
	printf("%d %d dead\n", cur_time() - t->cur_time, t->id);
	return (0);
}

int	one_philo(t_philo philo)
{
	if (pthread_create(&philo.thread, NULL, test1, &philo) != 0)
		return (1);
	pthread_join(philo.thread, NULL);
	return (0);
}

int	check_death(int ac, t_data *data, t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(&data->print);
		data->x = data->ate_max;
		pthread_mutex_unlock(&data->print);
		while (ac == 6 && data->x == data->number_of_philos)
		{
			pthread_mutex_lock(&data->print);
			data->etat = 1;
			pthread_mutex_unlock(&data->print);
			return (0);
		}
		pthread_mutex_lock(&data->print);
		data->last = philo->last_meal;
		pthread_mutex_unlock(&data->print);
		if ((cur_time() - philo->cur_time) - data->last > data->time_to_die)
		{
			pthread_mutex_lock(&data->print);
			printf("%d %d dead\n", cur_time() - philo->cur_time, philo->id);
			data->etat = 1;
			return (0);
		}
	}
}

int	main(int ac, char **av)
{
	int		i;
	t_data	data;
	t_philo	*philo;

	philo = NULL;
	i = 0;
	if (ac == 5 || ac == 6)
	{
		innit_args(&data, ac, av);
		if (check_args(ac, av) == 1)
			return (0);
		init_philo(&philo, &data);
		if (data.number_of_philos == 1)
			one_philo(*philo);
		else
		{
			create_philo(philo, data, i);
			check_death(ac, &data, philo);
			if (data.etat == 1)
				return (0);
			i = 0;
			join_thread(philo, data, i);
		}
	}
	return (0);
}
