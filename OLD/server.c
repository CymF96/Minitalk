/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cofische <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 14:41:11 by cofische          #+#    #+#             */
/*   Updated: 2024/07/18 14:41:12 by cofische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_msg	g_msg;

void	bit_reception(void)
{
	if (g_msg.received_bit != -1)
	{
		g_msg.c |= (g_msg.received_bit << g_msg.bit_position);
		g_msg.bit_position--;
		if (g_msg.bit_position < 0)
		{
			g_msg.message_received[g_msg.byte_index++] = g_msg.c;
			g_msg.c = 0;
			g_msg.bit_position = 7;
		}
		if (g_msg.byte_index == 4095)
		{
			g_msg.message_received[g_msg.byte_index++] = '\0';
			ft_printf("%s", g_msg.message_received);
			g_msg.byte_index = 0;
		}
		else if (g_msg.byte_index != 0
			&& g_msg.message_received[g_msg.byte_index - 1] == '\0')
		{
			ft_printf("%s\n", g_msg.message_received);
			g_msg.byte_index = 0;
		}
	}
}

void	reading_message(int sig)
{
	if (sig == SIGUSR1)
		g_msg.received_bit = 0;
	else if (sig == SIGUSR2)
		g_msg.received_bit = 1;
	else
		exit(EXIT_FAILURE);
	bit_reception();
}

int	main(void)
{
	struct sigaction	sa;

	ft_printf("Server %d, ready to talk!\n", getpid());
	sa.sa_handler = reading_message;
	sa.sa_flags = SA_RESTART | SA_NODEFER;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGUSR1, &sa, NULL) == -1
		|| sigaction(SIGUSR2, &sa, NULL) == -1)
	{
		ft_printf("Error handling the signal\n");
		exit(EXIT_FAILURE);
	}
	g_msg.byte_index = 0;
	g_msg.received_bit = -1;
	g_msg.c = 0;
	g_msg.bit_position = 7;
	while (1)
		pause();
	exit(EXIT_SUCCESS);
}
