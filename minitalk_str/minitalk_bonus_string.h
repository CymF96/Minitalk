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
# include <bits/siginfo-consts-arch.h>
# include "libft/libft.h"

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

int		error_check(int ac, char **av);
void	send_char(int server, char c);
void	send_string_size(int server, char *size_ptr);
void	message_receive(int sig);
void	receiving_len(void);
void	receiving_message(void);
void	initialisation(void);
void	reading_message(int sig, siginfo_t *info, void *context);

#endif
