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

int error_check(int ac, char **av)
{
    if (ac < 3)
    {
        ft_printf("not enough input\n");
        return (1);
    }
    if (av[1][0] == '\0')
    {
        ft_printf("Please enter a server pid to start talking\n");
        return (1);
    }
    if (av[2][0] == '\0')
    {
        ft_printf("No message to send\n");
        return (1);
    }
    return (0);
}

void send_char(int server, char c)
{
    int bit_index;
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
    	else
    	{
        	ft_printf("Invalid bit, communication stop\n");
        	exit(EXIT_FAILURE);
    	}
    	usleep(300);
	}
}

void send_string_size(int server, int size)
{
    char *size_str;
	
	size_str = ft_itoa(size);
    if (!size_str)
        exit(EXIT_FAILURE);
    while (*size_str != '\0')
        send_char(server, *size_str++);
    send_char(server, '\0');
}

void send_message(int server, char *message)
{
    while (*message != '\0')
        send_char(server, *message++);
    send_char(server, '\0');
}

int main(int ac, char **av)
{
    if (error_check(ac, av) != 0)
        exit(EXIT_FAILURE);
    int server = ft_atoi(av[1]);
    int message_size = ft_strlen(av[2]);
    send_string_size(server, message_size);
    send_message(server, av[2]);
    return 0;
}




// #include "minitalk.h"

// int	error_check(int ac, char **av)
// {
// 	if (ac < 3)
// 	{
// 		ft_printf("not enough input\n");
// 		return (1);
// 	}
// 	if (av[1][0] == '\0')
// 	{
// 		ft_printf("Please enter a server pid to start talking\n");
// 		return (1);
// 	}
// 	if (av[2][0] == '\0')
// 	{
// 		ft_printf("No message to send\n");
// 		return (1);
// 	}
// 	return (0);
// }

// void	send_end_message(int server, char c)
// {
// 	int	bit_index;
// 	int	bit;

// 	bit_index = 7;
// 	bit = -1;
// 	while (bit_index >= 0)
// 	{
// 		bit = (c >> bit_index--) & 1;
// 		if (bit == 0)
// 			kill(server, SIGUSR1);
// 		else if (bit == 1)
// 			kill(server, SIGUSR2);
// 		else
// 		{
// 			ft_printf("Invalid bit, communication stop\n");
// 			exit(EXIT_FAILURE);
// 		}
// 		usleep(300);
// 	}
// }

// void	send_string_size(int server, char *size)
// {
// 	int	bit_index;
// 	int	bit;

// 	bit_index = 7;
// 	bit = -1;
// 	while (size)
// 	{
// 		while (bit_index >= 0)
// 		{
// 			bit = (*size >> bit_index--) & 1;
// 			if (bit == 0)
// 				kill(server, SIGUSR1);
// 			else if (bit == 1)
// 				kill(server, SIGUSR2);
// 			else
// 			{
// 				ft_printf("Invalid bit, communication stop\n");
// 				exit(EXIT_FAILURE);
// 			}
// 			usleep(300);
// 		}
// 		size++;
// 	}
// }

// void	send_message(int server, char *av)
// {
// 	int	i;
// 	int	j;
// 	int	bit;

// 	i = 0;
// 	bit = -1;
// 	while (av[i] != '\0')
// 	{
// 		j = 7;
// 		while (j >= 0)
// 		{
// 			bit = (av[i] >> j--) & 1;
// 			if (bit == 0)
// 				kill(server, SIGUSR1);
// 			else if (bit == 1)
// 				kill(server, SIGUSR2);
// 			else
// 			{
// 				ft_printf("Invalid bit, communication stop\n");
// 				exit(EXIT_FAILURE);
// 			}
// 			usleep(300);
// 		}
// 		i++;
// 	}
// }

// int	main(int ac, char **av)
// {
// 	int	server;
// 	int message_size;

// 	if (error_check(ac, av) != 0)
// 		exit(EXIT_FAILURE);
// 	server = ft_atoi(av[1]);
// 	message_size = ft_strlen(av[2]);
// 	send_string_size(server, ft_itoa(message_size));
// 	send_end_message(server, '\0');
// 	send_message(server, av[2]);
// 	send_end_message(server, '\0');
// 	return (0);
// }
