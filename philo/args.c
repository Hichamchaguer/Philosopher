/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchaguer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 22:16:31 by hchaguer          #+#    #+#             */
/*   Updated: 2023/06/07 07:26:27 by hchaguer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	innit_args(t_data *data, int ac, char **av)
{
	data->number_of_philos = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->ate_max = 0;
	if (ac == 6)
		data->nb_of_times_each_philo_must_eat = ft_atoi(av[5]);
}

void	init_philo(t_philo **philo, t_data *data)
{
	int	i;

	i = 1;
	while (i <= data->number_of_philos)
	{
		ft_lstadd_back(philo, create_node(i, data));
		i++;
	}
}

int	check_args(int ac, char **av)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (is_integer(av[i]) == 1)
			return (1);
		if (ft_atoi(av[i]) == 0 || ft_atoi(av[i]) < 0)
			return (1);
		i++;
	}
	return (0);
}

int	cur_time(void)
{
	int				convert_time;
	struct timeval	time;

	gettimeofday(&time, NULL);
	convert_time = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (convert_time);
}

void	ft_wait(int time)
{
	int	c;

	c = cur_time();
	while (1)
	{
		if (cur_time() - c > time)
			break ;
		usleep(150);
	}
}
