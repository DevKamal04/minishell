/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhorvath <rhorvath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 17:33:27 by kamsingh          #+#    #+#             */
/*   Updated: 2024/06/13 05:05:50 by rhorvath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_export(char **command, t_terminal *terminal, int flag)
{
	if (command[1] == NULL)
		ft_print_export(terminal);
	else if (ft_strchr(command[1], '='))
		ft_add_export_env(terminal, command[1]);
	if (flag)
		exit(EXIT_SUCCESS);
	return (0);
}

void	ft_add_env(t_terminal *terminal, char *new_var)
{
	char	**new_env;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (terminal->env[i])
		i++;
	new_env = (char **)malloc(sizeof(char *) * (i + 2));
	if (!new_env)
	{
		perror("malloc");
		exit(1);
	}
	while (j < i)
	{
		new_env[j] = ft_strdup(terminal->env[j]);
		j++;
	}
	new_env[j] = ft_strdup(new_var);
	new_env[j + 1] = NULL;
	if (terminal->env)
		free_mat(terminal->env);
	j = 0;
	terminal->env = new_env;
}
