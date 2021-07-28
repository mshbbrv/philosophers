/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjonell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 23:16:15 by thjonell          #+#    #+#             */
/*   Updated: 2021/07/27 23:16:17 by thjonell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	eating(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_status(philo, FORK);
	pthread_mutex_lock(philo->right_fork);
	print_status(philo, FORK);
	print_status(philo, EAT);
	philo->last_meal_time = timestamp(philo->data->start_tv);
	mysleep(philo->data->time_to_eat * 1000);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	*simulation(void *arg)
{
	t_philo	*philo;
	int		meals_count;

	meals_count = 0;
	philo = (t_philo *)arg;
	usleep(100 * philo->id);
	while (philo->data->status == RUN)
	{
		eating(philo);
		meals_count++;
		if (philo->data->max_meals != -1
			&& meals_count == philo->data->max_meals)
		{
			philo->status = FULL;
			break ;
		}
		print_status(philo, SLEEP);
		mysleep(philo->data->time_to_sleep * 1000);
		print_status(philo, THINK);
	}
	return (NULL);
}

int	start_simulation(t_data *data)
{
	t_philo	*philo;

	gettimeofday(&data->start_tv, NULL);
	philo = data->philo_head;
	while (philo)
	{
		if (philo->id % 2 != 0)
			if (pthread_create(&philo->pthread, NULL, &simulation, philo))
				return (error_handler("Failed to create thread", data));
		philo = philo->next;
	}
	usleep(30000);
	philo = data->philo_head;
	while (philo)
	{
		if (philo->id % 2 == 0)
			if (pthread_create(&philo->pthread, NULL, &simulation, philo))
				return (error_handler("Failed to create thread", data));
		philo = philo->next;
	}
	return (0);
}

int	join_threads(t_data *data)
{
	t_philo	*philo;

	philo = data->philo_head;
	while (philo)
	{
		if (pthread_join(philo->pthread, NULL))
			return (error_handler("Failed to join thread", data));
		philo = philo->next;
	}
	return (0);
}
