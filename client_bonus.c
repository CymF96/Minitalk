/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cofische <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 14:40:57 by cofische          #+#    #+#             */
/*   Updated: 2024/07/23 18:12:59 by cofische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

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
		usleep(500);
	}
}

void	message_receive(int sig)
{
	if (sig == SIGUSR1)
		ft_printf("message received sucessfully\n");
	else if (sig == SIGUSR2)
		ft_printf("message not received\n");
	else
	{
		ft_printf("Error, no acknowledgment from server\n");
		exit(EXIT_FAILURE);
	}
}

int	main(int ac, char **av)
{
	struct sigaction	sa;
	int					server;

	if (error_check(ac, av) != 0)
		exit(EXIT_FAILURE);
	server = ft_atoi(av[1]);
	sa.sa_handler = message_receive;
	sa.sa_flags = SA_RESTART | SA_NODEFER;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGUSR1, &sa, NULL) == -1
		|| sigaction(SIGUSR2, &sa, NULL) == -1)
		exit(EXIT_FAILURE);
	while (*av[2] != '\0')
		send_char(server, *av[2]++);
	send_char(server, '\0');
	return (0);
}
