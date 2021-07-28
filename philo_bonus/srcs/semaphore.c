/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphore.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjonell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 23:14:03 by thjonell          #+#    #+#             */
/*   Updated: 2021/07/27 23:14:04 by thjonell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	init_sem(t_data *data)
{
	data->forks = sem_open("forks", O_CREAT, 0644, data->philo_num);
	if (data->forks == SEM_FAILED)
		return (error_handler("Failed to open semaphore", data));
	if (sem_unlink("forks"))
		return (error_handler("Failed to unlink semaphore", data));
	data->life_monitor = sem_open("life_monitor", O_CREAT, 0644, 1);
	if (data->life_monitor == SEM_FAILED)
		return (error_handler("Failed to open semaphore", data));
	if (sem_unlink("life_monitor"))
		return (error_handler("Failed to unlink semaphore", data));
	data->print_status = sem_open("print_status", O_CREAT, 0644, 1);
	if (data->print_status == SEM_FAILED)
		return (error_handler("Failed to open semaphore", data));
	if (sem_unlink("print_status"))
		return (error_handler("Failed to unlink semaphore", data));
	return (0);
}

int	close_sem(t_data *data)
{
	if (sem_close(data->forks))
		return (error_handler("Failed to close semaphore", data));
	if (sem_close(data->life_monitor))
		return (error_handler("Failed to close semaphore", data));
	if (sem_close(data->print_status))
		return (error_handler("Failed to close semaphore", data));
	return (0);
}
