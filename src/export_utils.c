/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhorvath <rhorvath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 18:41:50 by kamsingh          #+#    #+#             */
/*   Updated: 2024/06/13 05:04:24 by rhorvath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_print_export(t_terminal *terminal)
{
	char	**env;
	char	*sub;
	char	*sub2;
	int		i;
	int		ind;

	i = 0;
	env = terminal->env;
	while (env[i])
	{
		ind = check_equal(env[i]);
		if (ind == -1)
			printf("declare -x %s\n", env[i]);
		else
		{
			sub = ft_substr(env[i], 0, ind);
			sub2 = ft_substr(env[i], ind + 1, ft_strlen(env[i] + ind));
			printf("declare -x %s=\"%s\"\n", sub, sub2);
			if (sub)
				free(sub);
			if (sub2)
				free(sub2);
		}
		i++;
	}
}

int	check_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (-1);
}

int	export_helper(char **new_export_env, char **env, int j)
{
	new_export_env[j] = ft_strdup(env[j]);
	if (new_export_env[j] == NULL)
	{
		perror("ft_strdup");
		exit(1);
	}
	return (j);
}

void	export_mem_check(char **new_export_env)
{
	if (new_export_env == NULL)
	{
		perror("malloc");
		exit(1);
	}
}

void	ft_add_export_env(t_terminal *terminal, char *new_var)
{
	int		i;
	int		j;
	char	**new_export_env;

	i = 0;
	j = 0;
	while (terminal->env && terminal->env[i])
		i++;
	new_export_env = (char **)malloc(sizeof(char *) * (i + 2));
	export_mem_check(new_export_env);
	while (j < i)
	{
		j = export_helper(new_export_env, terminal->env, j);
		j++;
	}
	new_export_env[j] = ft_strdup(new_var);
	if (new_export_env[j] == NULL)
	{
		perror("ft_strdup");
		exit(1);
	}
	new_export_env[j + 1] = NULL;
	if (terminal->env)
		free_mat(terminal->env);
	terminal->env = new_export_env;
}
