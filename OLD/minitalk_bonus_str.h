/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cofische <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 14:41:24 by cofische          #+#    #+#             */
/*   Updated: 2024/07/18 14:41:26 by cofische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_BONUS_H
# define MINITALK_BONUS_H
# define _GNU_SOURCE

# include <unistd.h>
# include <signal.h>
# include <stdlib.h>
# include <bits/sigaction.h>
# include <bits/siginfo-consts-arch.h>
# include <asm-generic/signal-defs.h>
# include <sys/wait.h>
# include "../libft/libft.h"

typedef struct s_msg
{
	char					*message_received;
	char					*len_received;
	int						len;
	int						flag;
	int						bit_position;
	int						byte_index;
	int						c;
	int						client_pid;
	volatile sig_atomic_t	received_bit;
}	t_msg;

void	reading_message(int sig, siginfo_t *info, void *context);
void	bit_reconstruction(void);
int		error_check(int ac, char **av);
void	message_receive(int sig);
void	send_end_message(int server, char c);
void	send_message(int server, char *av);

#endif
