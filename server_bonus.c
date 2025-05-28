/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cofische <cofische@student.42london.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 17:41:13 by cofische          #+#    #+#             */
/*   Updated: 2024/07/24 17:44:51 by cofische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

static t_msg	g_msg;

void	print_message(void)
{
	if (g_msg.message[g_msg.byte_index - 1] == '\0')
	{
		g_msg.message[g_msg.byte_index] = '\0';
		kill(g_msg.client_pid, SIGUSR1);
		ft_printf("%s\n", g_msg.message);
		g_msg.byte_index = 0;
	}
	else
	{
		g_msg.message[g_msg.byte_index] = '\0';
		ft_printf("%s", g_msg.message);
		g_msg.byte_index = 0;
	}
}

void	reading_message(int sig, siginfo_t *info, void *context)
{
	(void)context;
	g_msg.client_pid = info->si_pid;
	if (sig == SIGUSR1)
		g_msg.received_bit = 0;
	else if (sig == SIGUSR2)
		g_msg.received_bit = 1;
	else
		kill(g_msg.client_pid, SIGUSR1);
	if (g_msg.received_bit != -1)
	{
		g_msg.c |= (g_msg.received_bit << g_msg.bit_position--);
		if (g_msg.bit_position < 0)
		{
			g_msg.message[g_msg.byte_index++] = g_msg.c;
			g_msg.c = 0;
			g_msg.bit_position = 7;
		}
		if (g_msg.byte_index == 4 || (g_msg.byte_index > 0
				&& (g_msg.message[g_msg.byte_index - 1] & 0xC0) != 0x80))
			print_message();
	}
	g_msg.received_bit = -1;
}

int	main(void)
{
	struct sigaction	sa;

	ft_printf("Server %d, ready to talk!\n", getpid());
	sa.sa_sigaction = reading_message;
	sa.sa_flags = SA_RESTART | SA_NODEFER | SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGUSR1, &sa, NULL) == -1
		|| sigaction(SIGUSR2, &sa, NULL) == -1)
	{
		ft_printf("Error handling the signal\n");
		exit(EXIT_FAILURE);
	}
	g_msg.bit_position = 7;
	g_msg.byte_index = 0;
	g_msg.c = 0;
	g_msg.received_bit = -1;
	g_msg.client_pid = 0;
	while (1)
		pause();
	return (0);
}
