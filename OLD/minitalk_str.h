/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cofische <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 14:41:19 by cofische          #+#    #+#             */
/*   Updated: 2024/07/18 14:41:20 by cofische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H
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
	volatile sig_atomic_t	received_bit;
}	t_msg;

void	reading_message(int sig);
void	bit_reception(void);
int		error_check(int ac, char **av);
void	send_end_message(int server, char c);
void	send_message(int server, char *av);

#endif
