/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjonell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 23:16:23 by thjonell          #+#    #+#             */
/*   Updated: 2021/07/27 23:16:24 by thjonell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	ft_putendl_fd(char *s, int fd)
{
	if (s != NULL)
	{
		ft_putstr_fd(s, fd);
		write(fd, "\n", 1);
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	int		i;
	char	str[10];

	if (n == -2147483648)
		write(fd, "-2147483648", 11);
	else
	{
		i = 0;
		if (n < 0)
		{
			write(fd, "-", 1);
			n *= -1;
		}
		else if (n == 0)
			str[i++] = 48;
		while (n)
		{
			str[i++] = n % 10 + 48;
			n /= 10;
		}
		i--;
		while (i >= 0)
			write(fd, &str[i--], 1);
	}
}

void	ft_putstr_fd(char *s, int fd)
{
	if (s != NULL)
		while (*s)
			write(fd, &(*s++), 1);
}

long	ft_atoi(const char *str)
{
	int			i;
	long long	result;
	long long	tmp;
	int			minus;

	minus = 1;
	result = 0;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if ((str[i] == '-' || str[i] == '+') && str[i++] == '-')
		minus = -1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		tmp = result;
		result = result * 10 + (str[i++] - 48);
		if (tmp > result && minus > 0)
			return (-1);
		else if (tmp > result)
			return (0);
	}
	if (result > LONG_MAX || result < LONG_MIN)
		return (LONG_MAX);
	return (result * minus);
}

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	else
		return (0);
}
