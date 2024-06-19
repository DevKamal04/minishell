/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhorvath <rhorvath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 01:28:52 by kamsingh          #+#    #+#             */
/*   Updated: 2024/06/12 22:57:03 by rhorvath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	echo_helper(int flag)
{
	write(1, "\n", 1);
	if (flag)
		exit(EXIT_SUCCESS);
	return (0);
}

int	exec_echo(char **command, int flag)
{
	int	line;
	int	i;

	i = 1;
	line = 1;
	if (command[1] == NULL)
		return (echo_helper(flag));
	if (command[1] && ft_strcmp(command[1], "-n") == 0)
	{
		line = 0;
		i++;
	}
	while (command[i])
	{
		write(1, command[i], ft_strlen(command[i]));
		if (command[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (line)
		write(1, "\n", 1);
	if (flag)
		exit(EXIT_SUCCESS);
	return (0);
}
