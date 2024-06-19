/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhorvath <rhorvath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 00:49:32 by kamsingh          #+#    #+#             */
/*   Updated: 2024/06/12 13:08:42 by rhorvath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	exec_env(t_terminal *terminal, int flag)
{
	char	**env;
	int		i;

	env = terminal->env;
	i = 0;
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
	if (flag)
		exit(EXIT_SUCCESS);
	return (0);
}

int	ft_pwd(t_terminal *terminal, int flag)
{
	int	i;

	i = 0;
	while (terminal->env[i])
	{
		if (ft_strncmp(terminal->env[i], "PWD", 3) == 0)
			printf("%s\n", terminal->env[i] + 4);
		i++;
	}
	if (flag)
		exit(EXIT_SUCCESS);
	return (0);
}
