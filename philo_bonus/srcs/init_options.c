/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_options.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjonell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 23:13:19 by thjonell          #+#    #+#             */
/*   Updated: 2021/07/27 23:13:23 by thjonell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	validate(long arg, t_data *data)
{
	if (arg <= 0)
		return (error_handler("Must be a positive number", data));
	if (arg == LONG_MAX)
		return (error_handler("Chill, this is too much :)", data));
	return (0);
}

int	parse_and_validate(t_data *data, char *argv[])
{
	data->philo_num = ft_atoi(argv[1]);
	if (validate(data->philo_num, data))
		return (1);
	data->time_to_die = ft_atoi(argv[2]);
	if (validate(data->time_to_die, data))
		return (1);
	data->time_to_eat = ft_atoi(argv[3]);
	if (validate(data->time_to_eat, data))
		return (1);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (validate(data->time_to_sleep, data))
		return (1);
	if (argv[5])
	{
		data->max_meals = ft_atoi(argv[5]);
		if (validate(data->max_meals, data))
			return (1);
	}
	return (0);
}

int	check_options(int argc, char *argv[], t_data *data)
{
	int	i;
	int	k;

	if (argc > 6 || argc < 5)
		return (error_handler("Invalid number of arguments", data));
	else
	{
		i = 0;
		while (++i < argc)
		{
			k = -1;
			while (argv[i][++k])
				if (!ft_isdigit(argv[i][k]))
					return (error_handler("Invalid input options", data));
		}
	}
	return (0);
}

void	init_data(t_data *data)
{
	data->philo_head = NULL;
	data->philo_num = 0;
	data->time_to_die = 0;
	data->time_to_eat = 0;
	data->time_to_sleep = 0;
	data->max_meals = -1;
	data->life_monitor = NULL;
	data->forks = NULL;
	data->full_count = 0;
	data->status = RUN;
	data->all_started.tv_sec = 0;
	data->all_started.tv_usec = 0;
}

int	init_options(t_data *data, int argc, char *argv[])
{
	init_data(data);
	if (check_options(argc, argv, data))
		return (1);
	if (parse_and_validate(data, argv))
		return (1);
	return (0);
}
