/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjonell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 23:15:36 by thjonell          #+#    #+#             */
/*   Updated: 2021/07/27 23:15:37 by thjonell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	print_status(t_philo *philo, char *str)
{
	struct timeval	ts;
	long			time_stamp;

	ts = timestamp(philo->data->start_tv);
	time_stamp = (ts.tv_sec * 1000000 + ts.tv_usec) / 1000;
	if (philo->data->status == RUN)
	{
		pthread_mutex_lock(philo->data->print_status);
		printf("%s%ld%s ", LIGHT, time_stamp, DEF);
		printf("%s%d%s ", BOLD, philo->id, DEF);
		if (str[3] == 'e')
			printf("%s%s%s\n", GREEN, str, DEF);
		else if (str[0] == 'h')
			printf("%s%s%s\n", YELLOW, str, DEF);
		else if (str[3] == 's')
			printf("%s%s%s\n", MAGENTA, str, DEF);
		else if (str[3] == 't')
			printf("%s%s%s\n", CYAN, str, DEF);
		else if (str[0] == 'd')
			printf("%s%s%s\n", RED, str, DEF);
		pthread_mutex_unlock(philo->data->print_status);
	}
}

struct timeval	timestamp(struct timeval start)
{
	struct timeval	current_tv;

	gettimeofday(&current_tv, NULL);
	current_tv.tv_sec -= start.tv_sec;
	current_tv.tv_usec -= start.tv_usec;
	if (current_tv.tv_usec < 0)
	{
		current_tv.tv_sec -= 1;
		current_tv.tv_usec += 1000000;
	}
	return (current_tv);
}

void	free_data(t_data *data)
{
	t_philo	*philo_tmp;

	if (data)
	{
		if (data->print_status)
			free(data->print_status);
		if (data->life_mutex)
			free(data->life_mutex);
		while (data->philo_head)
		{
			philo_tmp = data->philo_head->next;
			if (data->philo_head->left_fork)
			{
				free(data->philo_head->left_fork);
				data->philo_head->right_fork = NULL;
			}
			free(data->philo_head);
			data->philo_head = philo_tmp;
		}
		free(data);
	}
}

int	error_handler(char *str, t_data *data)
{
	ft_putendl_fd(str, STDERR_FILENO);
	free_data(data);
	return (1);
}

void	mysleep(long time)
{
	long			start;
	long			count;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	start = tv.tv_sec * 1000000 + tv.tv_usec;
	gettimeofday(&tv, NULL);
	count = tv.tv_sec * 1000000 + tv.tv_usec;
	while (count - start < time)
	{
		usleep(500);
		gettimeofday(&tv, NULL);
		count = tv.tv_sec * 1000000 + tv.tv_usec;
	}
}
