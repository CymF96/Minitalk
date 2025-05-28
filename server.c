/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cofische <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 14:41:11 by cofische          #+#    #+#             */
/*   Updated: 2024/07/24 17:46:44 by cofische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static t_msg	g_msg;

void	reading_message(int sig)
{
	if (sig == SIGUSR1)
		g_msg.received_bit = 0;
	else if (sig == SIGUSR2)
		g_msg.received_bit = 1;
	if (g_msg.received_bit != -1)
	{
		g_msg.c |= (g_msg.received_bit << g_msg.bit_position--);
		if (g_msg.bit_position < 0)
		{
			if (g_msg.c == '\0')
				ft_printf("\n");
			else
				ft_printf("%c", g_msg.c);
			g_msg.c = 0;
			g_msg.bit_position = 7;
		}
	}
	g_msg.received_bit = -1;
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
	g_msg.bit_position = 7;
	g_msg.c = 0;
	g_msg.received_bit = -1;
	while (1)
		pause();
	return (0);
}
