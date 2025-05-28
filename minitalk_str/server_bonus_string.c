/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cofische <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 14:41:04 by cofische          #+#    #+#             */
/*   Updated: 2024/07/18 14:41:05 by cofische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus_string.h"

static t_msg	g_msg;

void	receiving_len(void)
{
	g_msg.len_received[g_msg.byte_index++] = g_msg.c;
	g_msg.c = 0;
	g_msg.bit_position = 7;
	if (g_msg.byte_index != 0
		&& g_msg.len_received[g_msg.byte_index - 1] == '\0')
	{
		g_msg.len = ft_atoi(g_msg.len_received);
		g_msg.flag = 0;
		g_msg.byte_index = 0;
		if (g_msg.len_received != NULL)
		{
			free(g_msg.len_received);
			g_msg.len_received = NULL;
		}
	}
}

void	receiving_message(void)
{
	g_msg.message_received[g_msg.byte_index++] = g_msg.c;
	g_msg.c = 0;
	g_msg.bit_position = 7;
	if (g_msg.byte_index != 0
		&& g_msg.message_received[g_msg.byte_index - 1] == '\0')
	{
		kill(g_msg.client_pid, SIGUSR1);
		ft_printf("%s\n", g_msg.message_received);
		g_msg.byte_index = 0;
		if (g_msg.message_received != NULL)
		{
			free(g_msg.message_received);
			g_msg.message_received = NULL;
		}
		g_msg.flag = 1;
		g_msg.len = 0;
	}
}

void	initialisation(void)
{
	if (g_msg.len != 0)
	{
		if (g_msg.message_received == NULL)
		{
			g_msg.message_received = malloc(g_msg.len + 1);
			if (g_msg.message_received == NULL)
				exit(EXIT_FAILURE);
		}
	}
	else
	{
		if (g_msg.len_received == NULL)
		{
			g_msg.len_received = malloc(6000);
			if (g_msg.len_received == NULL)
				exit(EXIT_FAILURE);
		}
	}
}

void	reading_message(int sig, siginfo_t *info, void *context)
{
	(void)context;
	g_msg.client_pid = info->si_pid;
	initialisation();
	if (sig == SIGUSR1)
		g_msg.received_bit = 0;
	else if (sig == SIGUSR2)
		g_msg.received_bit = 1;
	else
	{
		kill(g_msg.client_pid, SIGUSR2);
		exit(EXIT_FAILURE);
	}
	if (g_msg.received_bit != -1)
	{
		g_msg.c |= (g_msg.received_bit << g_msg.bit_position--);
		if (g_msg.bit_position < 0)
		{
			if (g_msg.flag == 1)
				receiving_len();
			else
				receiving_message();
		}
	}
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
		exit(EXIT_FAILURE);
	g_msg.byte_index = 0;
	g_msg.received_bit = -1;
	g_msg.c = 0;
	g_msg.bit_position = 7;
	g_msg.len = 0;
	g_msg.flag = 1;
	g_msg.message_received = NULL;
	g_msg.len_received = NULL;
	while (1)
		pause();
	exit(EXIT_SUCCESS);
}
