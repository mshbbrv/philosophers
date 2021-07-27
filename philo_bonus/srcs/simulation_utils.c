/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjonell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 23:14:21 by thjonell          #+#    #+#             */
/*   Updated: 2021/07/27 23:14:23 by thjonell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

long	lifetime(t_philo *philo)
{
	struct timeval	ts;
	long			life_time;

	if (philo->last_meal_time.tv_sec == 0 && philo->last_meal_time.tv_usec == 0)
	{
		ts = timestamp(philo->data->all_started);
		life_time = (ts.tv_sec * 1000000 + ts.tv_usec) / 1000;
	}
	else
	{
		ts = timestamp(philo->data->all_started);
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

void	kill_philos(t_philo *philo)
{
	while (philo)
	{
		kill(philo->pid, SIGKILL);
		philo = philo->next;
	}
}

void	*life_monitor(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (philo->status == RUN)
	{
		if (lifetime(philo) > philo->data->time_to_die)
		{
			print_status(philo, DIED);
			philo->status = STOP;
			sem_post(philo->data->life_monitor);
			sem_post(philo->data->forks);
			sem_post(philo->data->forks);
		}
	}
	return (NULL);
}

void	*life_monitor_thread(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	sem_wait(data->life_monitor);
	if (data->status == RUN)
		kill_philos(data->philo_head);
	sem_post(data->life_monitor);
	return (NULL);
}

void	wait_child(t_philo *philo)
{
	int	status;

	while (philo)
	{
		waitpid(philo->pid, &status, 0);
		data->full_count++;
		philo = philo->next;
	}
	if (philo->data->full_count == philo->data->philo_num)
	{
		philo->data->status = STOP;
		sem_post(philo->data->life_monitor);
	}
}
