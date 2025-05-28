/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cofische <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 14:40:49 by cofische          #+#    #+#             */
/*   Updated: 2024/07/18 14:40:50 by cofische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	error_check(int ac, char **av)
{
	if (ac < 3)
	{
		ft_printf("not enough input\n");
		return (1);
	}
	if (av[1][0] == '\0')
	{
		ft_printf("Please enter a server pid to start talking\n");
		return (1);
	}
	if (av[2][0] == '\0')
	{
		ft_printf("No message to send\n");
		return (1);
	}
	return (0);
}

void	send_end_message(int server, char c)
{
	int	bit_index;
	int	bit;

	bit_index = 7;
	bit = -1;
	while (bit_index >= 0)
	{
		bit = (c >> bit_index--) & 1;
		if (bit == 0)
			kill(server, SIGUSR1);
		else if (bit == 1)
			kill(server, SIGUSR2);
		else
		{
			ft_printf("Invalid bit, communication stop\n");
			exit(EXIT_FAILURE);
		}
		usleep(300);
	}
}

void	send_message(int server, char *av)
{
	int	i;
	int	j;
	int	bit;

	i = 0;
	bit = -1;
	while (av[i] != '\0')
	{
		j = 7;
		while (j >= 0)
		{
			bit = (av[i] >> j--) & 1;
			if (bit == 0)
				kill(server, SIGUSR1);
			else if (bit == 1)
				kill(server, SIGUSR2);
			else
			{
				ft_printf("Invalid bit, communication stop\n");
				exit(EXIT_FAILURE);
			}
			usleep(300);
		}
		i++;
	}
}

int	main(int ac, char **av)
{
	int	server;

	if (error_check(ac, av) != 0)
		exit(EXIT_FAILURE);
	server = ft_atoi(av[1]);
	send_message(server, av[2]);
	send_end_message(server, '\0');
	return (0);
}
