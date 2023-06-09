/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchaguer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 20:21:57 by hchaguer          #+#    #+#             */
/*   Updated: 2023/06/05 02:49:48 by hchaguer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_philo(t_philo *philo)
{
	int	i;

	i = 0;
	philo->cur_time = cur_time();
	while (i < philo->number_of_philos)
	{
		philo->pid[i] = fork();
		if (philo->pid[i] == 0)
		{
			philo->id = i + 1;
			test(*philo);
		}
		i++;
	}
}

void	check_ac6(t_philo *philo)
{
	int	nb;

	nb = philo->nb_of_times_each_philo_must_eat;
	if (philo->ac == 6 && philo->n_time == nb)
		exit(1);
}

void	test(t_philo philo)
{
	sem_wait(philo.lst);
	gettimeofday(&philo.last_meal, NULL);
	sem_post(philo.lst);
	if (pthread_create(&philo.thread, NULL, check_death, &philo) != 0)
		return ;
	while (1)
	{
		check_ac6(&philo);
		eatt(&philo);
		sem_wait(philo.print);
		printf("%d %d is sleeping\n", cur_time() - philo.cur_time, philo.id);
		sem_post(philo.print);
		ft_wait(philo.time_to_sleep);
		sem_wait(philo.print);
		printf("%d %d is thinking\n", cur_time() - philo.cur_time, philo.id);
		sem_post(philo.print);
	}
}

void	eatt(t_philo *philo)
{
	sem_wait(philo->fork);
	sem_wait(philo->print);
	printf("%d %d has taken a fork\n", cur_time() - philo->cur_time, philo->id);
	sem_post(philo->print);
	sem_wait(philo->fork);
	sem_wait(philo->print);
	printf("%d %d has taken a fork\n", cur_time() - philo->cur_time, philo->id);
	sem_post(philo->print);
	sem_wait(philo->print);
	philo->n_time++;
	printf("%d %d is eating\n", cur_time() - philo->cur_time, philo->id);
	sem_post(philo->print);
	sem_wait(philo->lst);
	gettimeofday(&philo->last_meal, NULL);
	sem_post(philo->lst);
	ft_wait(philo->time_to_eat);
	sem_post(philo->fork);
	sem_post(philo->fork);
}
