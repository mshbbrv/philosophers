/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjonell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 23:16:02 by thjonell          #+#    #+#             */
/*   Updated: 2021/07/27 23:16:03 by thjonell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	meals_monitor(t_data *data)
{
	t_philo	*philo;
	int		count;

	count = 0;
	philo = data->philo_head;
	while (philo)
	{
		if (philo->status == FULL)
			count++;
		philo = philo->next;
	}
	if (count == data->philo_num)
		return (STOP);
	return (RUN);
}

long	lifetime(t_philo *philo)
{
	struct timeval	ts;
	long			life_time;

	if (philo->last_meal_time.tv_sec == 0 && philo->last_meal_time.tv_usec == 0)
	{
		ts = timestamp(philo->data->start_tv);
		life_time = (ts.tv_sec * 1000000 + ts.tv_usec) / 1000;
	}
	else
	{
		ts = timestamp(philo->data->start_tv);
		ts.tv_sec -= philo->last_meal_time.tv_sec;
		ts.tv_usec -= philo->last_meal_time.tv_usec;
		if (ts.tv_usec < 0)
		{
			ts.tv_sec -= 1;
			ts.tv_usec += 1000000;
		}
		life_time = (ts.tv_sec * 1000000 + ts.tv_usec) / 1000;
	}
	return (life_time);
}

void	check_philos(t_philo *philo)
{
	while (philo)
	{
		pthread_mutex_lock(philo->data->life_mutex);
		if (philo->status == RUN && lifetime(philo) > philo->data->time_to_die)
		{
			print_status(philo, DIED);
			philo->data->status = STOP;
			pthread_mutex_unlock(philo->right_fork);
			pthread_mutex_unlock(philo->left_fork);
			pthread_mutex_unlock(philo->data->life_mutex);
			break ;
		}
		if (meals_monitor(philo->data) == STOP)
		{
			philo->data->status = STOP;
			pthread_mutex_unlock(philo->right_fork);
			pthread_mutex_unlock(philo->left_fork);
			pthread_mutex_unlock(philo->data->life_mutex);
			break ;
		}
		pthread_mutex_unlock(philo->data->life_mutex);
		philo = philo->next;
		usleep(1000);
	}
}

void	*monitor(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (philo->data->status == RUN)
	{
		check_philos(philo);
		philo = (t_philo *)arg;
	}
	return (NULL);
}

int	life_monitor_start(t_data *data)
{
	if (malloc_mutex(&data->life_mutex, data))
		return (1);
	if (pthread_mutex_init(data->life_mutex, NULL))
		return (error_handler("Failed to init mutex", data));
	if (pthread_create(&data->life_monitor, NULL, &monitor, data->philo_head))
		return (error_handler("Failed to create thread", data));
	if (pthread_detach(data->life_monitor))
		return (error_handler("Failed to detach thread", data));
	if (pthread_mutex_destroy(data->life_mutex))
		return (error_handler("Failed to destroy status mutex", data));
	return (0);
}
