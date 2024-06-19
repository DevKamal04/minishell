/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhorvath <rhorvath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 00:49:55 by kamsingh          #+#    #+#             */
/*   Updated: 2024/06/13 09:51:55 by rhorvath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
		{
			return (*s1 - *s2);
		}
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

int	check_builtins(char **command, t_terminal *terminal, int flag)
{
	char	*t;

	t = command[0];
	if (ft_strncmp(t, "echo", 4) == 0)
		return (exec_echo(command, flag));
	if (ft_strncmp(t, "cd", 2) == 0)
		return (change_directory(command[1], terminal, flag));
	if (ft_strncmp(t, "export", 6) == 0)
		return (ft_export(command, terminal, flag));
	if (ft_strncmp(t, "unset", 5) == 0)
		return (ft_unset(command, terminal, flag));
	if (ft_strncmp(t, "env", 3) == 0)
		return (exec_env(terminal, flag));
	if (ft_strncmp(t, "exit", 4) == 0)
		return (ft_exit(command, terminal));
	if (ft_strncmp(t, "pwd", 3) == 0)
		return (ft_pwd(terminal, flag));
	return (0);
}

int	check_fork(char **command)
{
	char	*t;

	if (command && command[0])
	{
		t = command[0];
		if (ft_strncmp(t, "echo", 4) == 0)
			return (1);
		if (ft_strncmp(t, "cd", 2) == 0)
			return (1);
		if (ft_strncmp(t, "export", 6) == 0)
			return (1);
		if (ft_strncmp(t, "unset", 5) == 0)
			return (1);
		if (ft_strncmp(t, "env", 3) == 0)
			return (1);
		if (ft_strncmp(t, "exit", 4) == 0)
			return (1);
	}
	return (0);
}
