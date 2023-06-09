/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchaguer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 22:57:09 by hchaguer          #+#    #+#             */
/*   Updated: 2023/06/06 22:15:49 by hchaguer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "philo.h"

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	is_integer(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(ft_isdigit(str[i])))
			return (1);
		i++;
	}
	return (0);
}

void	ft_lstadd_back(t_philo **head, t_philo *node1)
{
	t_philo	*cur;

	if (!head && !(*head))
		return ;
	else if (head && *head)
	{
		cur = *head;
		while (cur->next && cur->next != *head)
			cur = cur->next;
		cur->next = node1;
		node1->next = *head;
	}
	else
		*head = node1;
}

t_philo	*create_node(int id, t_data *data)
{
	t_philo	*node;

	node = malloc(sizeof(t_philo));
	if (!node)
		return (NULL);
	node->data = data;
	node->id = id;
	node->last_meal = 0;
	data->etat = 0;
	node->cur_time = cur_time();
	pthread_mutex_init(&node->fork, NULL);
	pthread_mutex_init(&data->print, NULL);
	node->next = NULL;
	return (node);
}
