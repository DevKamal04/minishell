/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhorvath <rhorvath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 04:05:19 by kamsingh          #+#    #+#             */
/*   Updated: 2024/06/13 08:55:34 by rhorvath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	change_env_variable(t_terminal *terminal,
	const char*variable_name, const char *new_value)
{
	char	**env;
	int		i;
	size_t	new_env_var_len;
	char	*new_env_var;

	i = 0;
	env = terminal->env;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], variable_name, ft_strlen(variable_name)) == 0
			&& env[i][ft_strlen(variable_name)] == '=')
		{
			if (env[i])
				free(env[i]);
			new_env_var_len = ft_strlen(variable_name)
				+ ft_strlen(new_value) + 2;
			new_env_var = malloc(new_env_var_len) + 1;
			new_env_var = new_strjoin(variable_name, new_value, "=");
			env[i] = new_env_var;
			return ;
		}
		i++;
	}
}

char	*new_strjoin(const char *s1, const char *s2, const char *sep)
{
	size_t	total_length;
	char	*result;

	total_length = strlen(s1) + strlen(s2) + strlen(sep) + 1;
	result = malloc(total_length);
	if (result == NULL)
		exit(EXIT_FAILURE);
	ft_strlcpy(result, s1, total_length);
	ft_strlcat(result, sep, total_length);
	ft_strlcat(result, s2, total_length);
	return (result);
}

char	*cd_path_helper(char *new_dir,
	char *oldpwd, char **final_dir, char **env)
{
	if (!new_dir)
		main_directory(env, final_dir);
	else if (ft_strcmp(new_dir, "..") == 0)
		change_directory_parent(oldpwd, final_dir);
	else if (new_dir[0] == '~')
		main_directory(env, final_dir);
	else if (new_dir[0] == '/')
		*final_dir = ft_strdup(new_dir);
	else if (new_dir[0] == '-')
		helper_minus_dir(env, final_dir);
	else if (new_dir[0] == '.')
		*final_dir = ft_strdup(oldpwd);
	return (*final_dir);
}

int	change_directory(char *new_dir, t_terminal *terminal, int flag)
{
	char	oldpwd[1024];
	char	*final_dir;
	char	**env;

	final_dir = NULL;
	env = terminal->env;
	if (getcwd(oldpwd, sizeof(oldpwd)) == NULL)
		return (1);
	if (cd_path_helper(new_dir, oldpwd, &final_dir, env) == NULL)
	{
		final_dir = ft_strjoin(oldpwd, "/");
		final_dir = ft_strjoin(final_dir, new_dir);
	}
	if (chdir(final_dir) != 0)
	{
		perror("Failed to change directory");
		free(final_dir);
		return (1);
	}
	change_env_variable(terminal, "PWD", final_dir);
	change_env_variable(terminal, "OLDPWD", oldpwd);
	free(final_dir);
	if (flag)
		exit(EXIT_SUCCESS);
	return (0);
}
