/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_help.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhorvath <rhorvath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 23:45:53 by kamsingh          #+#    #+#             */
/*   Updated: 2024/06/12 22:55:57 by rhorvath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	change_directory_parent(char *oldpwd, char **final_dir)
{
	int	i;

	i = 0;
	while (oldpwd[i])
		i++;
	i--;
	while (oldpwd[i])
	{
		if (oldpwd[i] == '/')
			break ;
		i--;
	}
	*final_dir = ft_substr(oldpwd, 0,
			ft_strlen(oldpwd) - (ft_strlen(oldpwd + i)));
	return (0);
}

int	main_directory(char **env, char **final_dir)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], "HOME=", ft_strlen("HOME=")) == 0)
		{
			final_dir[0] = ft_strdup(env[i] + ft_strlen("HOME="));
			break ;
		}
		i++;
	}
	if (final_dir[0] == NULL)
	{
		perror("Failed to create final direct hndffhjddjhory path");
		return (1);
	}
	return (0);
}

int	change_directory_path(char *base_path, char *new_value, char **final_dir)
{
	final_dir[0] = new_strjoin(base_path, new_value, "/");
	if (final_dir[0] == NULL)
	{
		perror("Failed to create final direct hndffhjddjhory path");
		return (1);
	}
	return (0);
}

int	helper_new_dir(char **env, char *new_dir, char **final_dir)
{
	int		i;
	char	*home_dir;

	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], "HOME=", ft_strlen("HOME=")) == 0)
		{
			home_dir = env[i] + ft_strlen("HOME=");
			if (change_directory_path(home_dir, new_dir + 1, final_dir) != 0)
				return (1);
			break ;
		}
		i++;
	}
	return (0);
}

int	helper_minus_dir(char **env, char **final_dir)
{
	int		i;
	char	*old_dir;

	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], "OLDPWD=", ft_strlen("OLDPWD=")) == 0)
		{
			old_dir = env[i] + ft_strlen("OLDPWD=");
			*final_dir = ft_strdup(old_dir);
			if (*final_dir == NULL)
			{
				perror("Failed to duplicate old directory");
				return (1);
			}
			break ;
		}
		i++;
	}
	return (0);
}
