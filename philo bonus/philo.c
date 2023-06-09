/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchaguer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 20:21:41 by hchaguer          #+#    #+#             */
/*   Updated: 2023/06/07 22:36:33 by hchaguer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_time(struct timeval last)
{
	int	t;

	t = last.tv_sec * 1000 + last.tv_usec / 1000;
	return (t);
}

void	*check_death(void *t1)
{
	t_philo	*philo;

	philo = (t_philo *)t1;
	while (1)
	{
		if (cur_time() - get_time(philo->last_meal) > philo->time_to_die)
		{
			sem_wait(philo->print);
			printf("%d %d dead\n", cur_time() - philo->cur_time, philo->id);
			exit(1);
		}
		usleep(150);
	}
}

void	ft_kill(t_philo philo)
{
	int	i;

	i = 0;
	while (i < philo.number_of_philos)
	{
		kill(philo.pid[i], SIGKILL);
		i++;
	}
}

int	main(int ac, char **av)
{
	int		status;
	t_philo	philo;

	if (ac == 5 || ac == 6)
	{
		innit_args(&philo, ac, av);
		if (check_args(ac, av) == 1)
			return (0);
		philo.print = sem_open("print", O_CREAT, 777, 1);
		philo.lst = sem_open("lst", O_CREAT, 777, 1);
		init_philo(&philo);
		create_philo(&philo);
		waitpid(-1, &status, 0);
		if (WEXITSTATUS(status) == 1)
			ft_kill(philo);
		sem_close(philo.print);
		sem_close(philo.fork);
		sem_close(philo.lst);
	}
	return (0);
}
