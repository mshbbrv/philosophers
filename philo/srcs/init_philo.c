/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjonell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 23:15:54 by thjonell          #+#    #+#             */
/*   Updated: 2021/07/27 23:15:56 by thjonell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	malloc_mutex(pthread_mutex_t **mutex, t_data *data)
{
	*mutex = malloc(sizeof(pthread_mutex_t));
	if (!*mutex)
		return (error_handler("Failed to allocate memory", data));
	return (0);
}

int	give_forks(t_philo *philo_head, t_data *data)
{
	t_philo	*philo;

	philo = philo_head;
	while (philo)
	{
		if (malloc_mutex(&philo->left_fork, data))
			return (1);
		if (philo->next)
			philo->next->right_fork = philo->left_fork;
		else
			philo_head->right_fork = philo->left_fork;
		philo = philo->next;
	}
	return (0);
}

void	init_philo_struct(t_philo *philo)
{
	philo->id = 0;
	philo->status = RUN;
	philo->last_meal_time.tv_sec = 0;
	philo->last_meal_time.tv_usec = 0;
	philo->pthread = NULL;
	philo->left_fork = NULL;
	philo->right_fork = NULL;
	philo->data = NULL;
	philo->next = NULL;
}

t_philo	*new_philo(t_data *data, int id)
{
	t_philo	*new_philo;

	new_philo = malloc(sizeof(t_philo));
	if (!new_philo)
	{
		error_handler("Failed to allocate memory", data);
		return (NULL);
	}
	init_philo_struct(new_philo);
	new_philo->id = id;
	new_philo->next = NULL;
	new_philo->data = data;
	return (new_philo);
}

int	init_philo(t_data *data)
{
	int		i;
	t_philo	*philo;
	t_philo	*tmp_philo;

	philo = new_philo(data, 1);
	data->philo_head = philo;
	i = 2;
	while (i < data->philo_num + 1)
	{
		tmp_philo = new_philo(data, i);
		philo->next = tmp_philo;
		philo = philo->next;
		i++;
	}
	if (give_forks(data->philo_head, data))
		return (1);
	if (malloc_mutex(&data->print_status, data))
		return (1);
	return (0);
}
