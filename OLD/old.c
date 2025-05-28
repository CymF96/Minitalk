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

#include "minitalk_bonus.h"

t_msg	*g_msg = NULL;

void	print_message(void)
{
	g_msg->str[g_msg->byte_index] = '\0';
	ft_printf("%s", g_msg->str);
	free(g_msg);
	g_msg = NULL;
}

void	bit_reconstruction(void)
{
	if (g_msg->c == '\0')
	{
		kill(g_msg->client_pid, SIGUSR1);
		print_message();
		ft_printf("\n");
		return ;
	}
	else
	{
		g_msg->str[g_msg->byte_index++] = g_msg->c;
		g_msg->c = 0;
		g_msg->bit_position = 7;
	}
}

void	bit_reception(void)
{
	if (g_msg->received_bit != -1)
	{
		g_msg->c |= (g_msg->received_bit << g_msg->bit_position);
		g_msg->bit_position--;
		if (g_msg->bit_position < 0)
		{
			bit_reconstruction();
			if (g_msg == NULL)
				return ;
		}
		if (g_msg->byte_index > 0
			&& (g_msg->str[g_msg->byte_index - 1] & 0xC0) != 0x80)
		{
			if (g_msg->byte_index >= 4 || (g_msg->byte_index > 0
					&& (g_msg->str[g_msg->byte_index - 1] & 0xC0) != 0x80))
				print_message();
		}
	}
}

void	reading_message(int sig, siginfo_t *info, void *context)
{
	(void)context;
	if (g_msg == NULL)
	{
		g_msg = malloc(sizeof(t_msg));
		if (!g_msg)
			exit(EXIT_FAILURE);
		g_msg->bit_position = 7;
		g_msg->byte_index = 0;
		g_msg->client_pid = info->si_pid;
		g_msg->received_bit = -1;
		g_msg->c = 0;
	}
	if (sig == SIGUSR1)
		g_msg->received_bit = 0;
	else if (sig == SIGUSR2)
		g_msg->received_bit = 1;
	else
	{
		kill(g_msg->client_pid, SIGUSR2);
		free(g_msg);
		exit(EXIT_FAILURE);
	}
	bit_reception();
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
	while (1)
		pause();
	return (0);
}
