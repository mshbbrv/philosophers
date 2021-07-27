/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjonell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 23:14:12 by thjonell          #+#    #+#             */
/*   Updated: 2021/07/27 23:14:16 by thjonell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	eating(t_philo *philo)
{
	sem_wait(philo->data->forks);
	print_status(philo, FORK);
	sem_wait(philo->data->forks);
	print_status(philo, FORK);
	print_status(philo, EAT);
	philo->last_meal_time = timestamp(philo->data->all_started);
	mysleep(philo->data->time_to_eat * 1000);
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
}

void	simulation(t_philo *philo)
{
	philo->meals_count = 0;
	if (pthread_create(&philo->pthread, NULL, &life_monitor, philo))
		error_handler("Failed to create thread", philo->data);
	if (pthread_detach(philo->pthread))
		error_handler("Failed to detach thread", philo->data);
	while (philo->status == RUN)
	{
		eating(philo);
		philo->meals_count++;
		if (philo->data->max_meals != -1
			&& philo->meals_count == philo->data->max_meals)
		{
			philo->status = STOP;
			break ;
		}
		print_status(philo, SLEEP);
		mysleep(philo->data->time_to_sleep * 1000);
		print_status(philo, THINK);
	}
	exit(0);
}

void	create_child(t_philo *philo)
{
	while (philo)
	{
		philo->pid = fork();
		if (philo->pid < 0)
			error_handler("Failed to create fork", data);
		else if (philo->pid == 0)
			simulation(philo);
		philo = philo->next;
	}
}

void	*philos_thread(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	sem_wait(data->life_monitor);
	gettimeofday(&data->all_started, NULL);
	create_child(data->philo_head);
	wait_child(data->philo_head);
	return (NULL);
}

int	start_simulation(t_data *data)
{
	if (pthread_create(&data->philos_th, NULL, &philos_thread, data))
		return (error_handler("Failed to create thread", data));
	if (pthread_create(&data->life_monitor_th, NULL, &life_monitor_thread,
			   data))
		return (error_handler("Failed to create thread", data));
	if (pthread_join(data->philos_th, NULL))
		return (error_handler("Failed to join thread", data));
	if (pthread_join(data->life_monitor_th, NULL))
		return (error_handler("Failed to join thread", data));
	return (0);
}
