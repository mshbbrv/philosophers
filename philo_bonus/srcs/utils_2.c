/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjonell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 23:14:38 by thjonell          #+#    #+#             */
/*   Updated: 2021/07/27 23:14:39 by thjonell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	print_status(t_philo *philo, char *str)
{
	struct timeval	ts;
	long			time_stamp;

	sem_wait(philo->data->print_status);
	ts = timestamp(philo->data->all_started);
	time_stamp = (ts.tv_sec * 1000000 + ts.tv_usec) / 1000;
	if (philo->status == RUN)
	{
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
	}
	sem_post(philo->data->print_status);
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
		if (data->forks)
			free(data->forks);
		if (data->life_monitor)
			free(data->life_monitor);
		if (data->print_status)
			free(data->print_status);
		while (data->philo_head)
		{
			philo_tmp = data->philo_head->next;
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
		usleep(50);
		gettimeofday(&tv, NULL);
		count = tv.tv_sec * 1000000 + tv.tv_usec;
	}
}
