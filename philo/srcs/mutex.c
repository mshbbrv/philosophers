/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjonell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 23:16:08 by thjonell          #+#    #+#             */
/*   Updated: 2021/07/27 23:16:09 by thjonell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	init_mutex(t_data *data)
{
	t_philo	*philo;

	philo = data->philo_head;
	while (philo)
	{
		if (pthread_mutex_init(philo->left_fork, NULL))
			return (error_handler("Failed to init mutex", data));
		philo = philo->next;
	}
	if (pthread_mutex_init(data->print_status, NULL))
		return (error_handler("Failed to init mutex", data));
	return (0);
}

int	destroy_mutex(t_data *data)
{
	t_philo	*philo;

	philo = data->philo_head;
	while (philo)
	{
		if (pthread_mutex_destroy(philo->left_fork))
			return (error_handler("Failed to destroy philo mutex", data));
		philo = philo->next;
	}
	if (pthread_mutex_destroy(data->print_status))
		return (error_handler("Failed to destroy status mutex", data));
	return (0);
}
