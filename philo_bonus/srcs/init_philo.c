/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjonell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 23:13:39 by thjonell          #+#    #+#             */
/*   Updated: 2021/07/27 23:13:42 by thjonell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	init_philo_struct(t_philo *philo)
{
	philo->id = 0;
	philo->status = RUN;
	philo->last_meal_time.tv_sec = 0;
	philo->last_meal_time.tv_usec = 0;
	philo->pid = 0;
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
	return (0);
}
