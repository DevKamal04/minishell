/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhorvath <rhorvath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 12:23:49 by kamsingh          #+#    #+#             */
/*   Updated: 2024/06/13 02:24:00 by rhorvath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_exit(char **command, t_terminal *terminal)
{
	int	status;
	int	i;

	i = 0;
	status = 0;
	terminal->exit_status = 0;
	while (command && command[i])
		i++;
	ft_putstr_fd("exit\n", 2);
	if (i > 2)
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
	if (i == 2)
	{
		status = ft_atoi(command[1]);
		while (command[1][i])
		{
			if (!ft_isdigit(command[1][i]))
				status = 255;
		}
	}
	terminal->exit_flag = 1;
	return ((char) status);
}
