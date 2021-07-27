/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjonell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 23:15:27 by thjonell          #+#    #+#             */
/*   Updated: 2021/07/27 23:15:28 by thjonell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	main(int argc, char *argv[])
{
	t_data			*data;

	data = malloc(sizeof(t_data));
	if (init_options(data, argc, argv))
		return (1);
	if (init_philo(data))
		return (1);
	if (init_mutex(data))
		return (1);
	if (start_simulation(data))
		return (1);
	if (life_monitor_start(data))
		return (1);
	if (join_threads(data))
		return (1);
	if (destroy_mutex(data))
		return (1);
	return (0);
}
