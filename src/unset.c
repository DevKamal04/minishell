/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhorvath <rhorvath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 16:54:21 by kamsingh          #+#    #+#             */
/*   Updated: 2024/06/13 11:40:28 by rhorvath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_unset(char **a, t_terminal *terminal, int flag)
{
	char	**env;
	int		i;

	if (a[0] == NULL || ft_strlen(a[0]) <= 0)
		return (ft_putstr_fd("ERROR", 2), 1);
	env = terminal->env;
	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], a[1], ft_strlen(a[1])) == 0
			&& env[i][ft_strlen(a[1])] == '=')
		{
			ft_realloc(i, terminal);
			return (0);
		}
		i++;
	}
	ft_putstr_fd("NOT FOUND", 2);
	if (flag)
		exit(EXIT_SUCCESS);
	return (1);
}

void	free_mat(char **mat)
{
	int	i;

	i = 0;
	if (!mat)
		return ;
	while (mat && mat[i])
	{
		if (mat[i])
			free(mat[i]);
		i++;
	}
	if (mat)
		free(mat);
}

void	ft_realloc(int ind, t_terminal *terminal)
{
	char	**new_env;
	int		i;
	int		j;

	i = 0;
	while (terminal->env[i])
		i++;
	new_env = (char **)malloc(sizeof(char *) * i);
	new_env[i] = 0;
	i = 0;
	j = 0;
	while (terminal->env[i])
	{
		if (i == ind)
			i++;
		else
		{
			new_env[j] = ft_strdup(terminal->env[i]);
			i++;
			j++;
		}
	}
	free_mat(terminal->env);
	terminal->env = new_env;
}

int	is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	return (0);
}
