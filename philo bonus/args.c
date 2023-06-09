/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchaguer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 20:21:30 by hchaguer          #+#    #+#             */
/*   Updated: 2023/06/07 04:55:44 by hchaguer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	innit_args(t_philo *philo, int ac, char **av)
{
	philo->number_of_philos = ft_atoi(av[1]);
	philo->time_to_die = ft_atoi(av[2]);
	philo->time_to_eat = ft_atoi(av[3]);
	philo->time_to_sleep = ft_atoi(av[4]);
	philo->ac = ac;
	if (ac == 6)
		philo->nb_of_times_each_philo_must_eat = ft_atoi(av[5]);
}

void	init_philo(t_philo *philo)
{
	sem_unlink("philo");
	sem_unlink("print");
	sem_unlink("lst");
	philo->etat = 0;
	philo->ate_max = 0;
	philo->cur_time = cur_time();
	philo->n_time = 0;
	philo->fork = sem_open("philo", O_CREAT, 777, philo->number_of_philos);
	philo->pid = malloc(philo->number_of_philos * sizeof(t_philo));
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

unsigned int	cur_time(void)
{
	unsigned int	convert_time;
	struct timeval	time;

	gettimeofday(&time, NULL);
	convert_time = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (convert_time);
}

void	ft_wait(unsigned int time)
{
	unsigned int	c;

	c = cur_time();
	while (1)
	{
		if (cur_time() - c >= time)
			break ;
		usleep(150);
	}
}
