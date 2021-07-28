/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjonell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 23:13:49 by thjonell          #+#    #+#             */
/*   Updated: 2021/07/27 23:13:52 by thjonell         ###   ########.fr       */
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
	if (init_sem(data))
		return (1);
	if (start_simulation(data))
		return (1);
	if (close_sem(data))
		return (1);
	free_data(data);
	return (0);
}
