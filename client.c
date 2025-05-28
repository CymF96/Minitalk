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
	if (av[2][0] == '\0')
	{
		ft_printf("No message to send\n");
		return (1);
	}
	return (0);
}

void	send_char(int server, char c)
{
	int	bit_index;
	int	bit;

	bit = -1;
	bit_index = 7;
	while (bit_index >= 0)
	{
		bit = (c >> bit_index--) & 1;
		if (bit == 0)
		{
			if (kill(server, SIGUSR1) == -1)
				exit(EXIT_FAILURE);
		}
		else if (bit == 1)
		{
			if (kill(server, SIGUSR2) == -1)
				exit(EXIT_FAILURE);
		}
		usleep(400);
	}
}

int	main(int ac, char **av)
{
	int		server;

	if (error_check(ac, av) != 0)
		exit(EXIT_FAILURE);
	server = ft_atoi(av[1]);
	while (*av[2] != '\0')
		send_char(server, *av[2]++);
	send_char(server, '\0');
	return (0);
}
